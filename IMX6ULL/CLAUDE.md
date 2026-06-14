# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

IMX6ULL bare-metal driver project for NXP i.MX6ULL (ARM Cortex-A7). No operating system — code runs directly on the hardware after being loaded by U-Boot. The default link address (`0x87800000`) is the DDR load address usable via `bootm` after U-Boot.

## Build Commands

```bash
make              # Build all test programs
make <test_name>  # Build a specific test (e.g., make Key, make SDK_LEDC)
make clean        # Clean all test builds
```

Overridable variables:
```bash
make C_LED CROSS_COMPILE=arm-none-eabi-  # Different toolchain prefix
make C_LED TARGET=myapp                  # Change output binary name
make C_LED LINK_ADDR=0x87800000          # Change link address (assembly-only projects; C projects use the link script which hardcodes 0x87800000)
```

Default toolchain: `arm-linux-gnueabihf-`. Build produces `.elf`, `.bin`, and `.dis` (disassembly) files in each test directory. The `.dis` file is essential for bare-metal debugging — inspecting generated code, verifying link addresses, and troubleshooting startup issues.

**Important:** For C projects, `LINK_ADDR` has no effect because `Common/lds/imx6u.lds` hardcodes `0x87800000`. To change the link address for a C project, either provide a custom `.lds` file in the test directory or edit the link script directly.

## Architecture

Three-layer separation:

1. **`Common/`** — Chip-level infrastructure shared by everything. Startup code (`start.s`), link script (`imx6u.lds`), NXP SDK headers (`MCIMX6Y2.h`, `fsl_common.h`, `fsl_iomuxc.h`), self-built register structs (`imx6u.h`), and the build system (`generic.mk`).

2. **`Driver/`** — Reusable peripheral driver API libraries. Each subdirectory is a self-contained driver (GPIO, Delay, Beep, Key, LED, Clock). These have **no `main()` function** — they are pure libraries compiled into tests automatically by `generic.mk`.

3. **`Test/`** — Standalone test programs, each with a `main()` function. One subdirectory per test. New test directories need only source files — no Makefile required. `generic.mk` auto-detects C vs. assembly projects and sets up the build accordingly.

The [README.md](README.md) contains detailed driver API tables, test comparison tables (showing how each test demonstrates a different register-access style), and NXP SDK porting notes.

## Memory Layout

| Region | Address | Source |
|--------|---------|--------|
| Code/text | `0x87800000` | `imx6u.lds` (DDR load address) |
| Stack | `0x80200000` | `start.s` (grows downward) |
| BSS | After `.data` | Zeroed by `start.s` before `main()` |

The link script requires `start.o` to be the first object in `.text` (so `_start` is at the entry point). BSS zeroing uses `stmia` with `ble` — this writes one extra word past `__bss_end` but is harmless (it overwrites already-zeroed memory or unused space).

## Key Design Patterns

### Auto-discovery build system

`Common/generic.mk` is the core build engine. For C projects, it automatically:
- Pulls in `Common/src/start.s` (startup + BSS zeroing + stack init)
- Pulls in the link script from `Common/lds/`
- Scans **all** `Driver/*/` subdirectories for `.c` files and compiles them into the test — no need to list dependencies explicitly
- Adds `Common/include/` and all `Driver/*/` dirs to the include path

For assembly-only projects (like `Test/S_LED`), it skips Common infrastructure and uses `-Ttext` direct linking.

### Adding a new driver

1. Create `Driver/<name>/<name>.c` and `Driver/<name>/<name>.h`
2. Driver `.c` files are auto-discovered by `generic.mk` — no changes to build files needed
3. Include the header in test `main.c` and call the driver APIs

### Adding a new test

1. Create `Test/<name>/` with at least a `main.c` (or `.s` for assembly)
2. Run `make <name>` — no Makefile needed

### Register access patterns

The codebase uses two styles side-by-side:
- **Self-built structs** (`imx6u.h`): `GPIO1->GDIR |= (1 << pin)`, `CCM->CCGR0 |= ...`
- **NXP SDK macros** (`fsl_iomuxc.h`): `IOMUXC_SetPinMux(...)`, `IOMUXC_SetPinConfig(...)`

`GPIO_Type`, `CCM_Type`, `CCM_ANALOG_Type`, etc. are defined in `imx6u.h` as structs with `volatile uint32_t` fields, then cast to base addresses via macros like `#define GPIO1 ((GPIO_Type *)0x0209C000)`. Note that `CCM` and `CCM_ANALOG` are **separate register blocks** at different base addresses (`0x020C4000` and `0x020C8000` respectively).

NXP SDK helper macros from `fsl_common.h` are used for bit manipulation:
- `SET_REG_FIELD(reg, msb, lsb, val)` — set a bit field
- `GET_REG_BIT(reg, bit)` — read a single bit
- `CLR_REG_BIT(reg, bit)` — clear a single bit

### File-local functions

Use the `LOCAL` macro (defined as `static` in `Common/include/type.h`) for functions that should not be exposed outside their translation unit. This is the project convention — never write `static` directly.

### Startup sequence (start.s)

1. Enter SVC mode (supervisor)
2. Zero the BSS section using `__bss_start`/`__bss_end` symbols from the link script
3. Set stack pointer to `0x80200000`
4. Branch to `main()`

## Peripheral init pattern

All driver init functions follow the same sequence:
```
Enable clocks (CCM CCGR0~6) → Configure IOMUX pin mux + pad → Set GPIO direction → Use
```

The `CCGRx_VALUE` macro (typically `0xFFFFFFFF` to enable all clocks) and `IOMUXC_SetPinMux`/`IOMUXC_SetPinConfig` from the NXP SDK are the standard way to perform clock and pin setup.

## Clock system

The `Driver/Clock` driver provides system clock initialization. It must be called before any peripheral that depends on specific clock frequencies:

- `system_clock_init_528mhz()` — configures the system for 528 MHz operation
- `system_clock_init_696mhz()` — configures the system for 696 MHz operation
- `device_clock_enable()` — enables clocks on all CCGR0~6 peripheral clock gates

Internally, clock init configures:
1. **PLL2 PFD clocks** (PFD0~3): 352/594/396/297 MHz (PFD2 at 396 MHz feeds DDR)
2. **PLL3 PFD clocks** (PFD0~3): 720/540/508/454 MHz
3. **AHB root clock**: sourced from PLL2 PFD2 (396 MHz), divided by 3 → 132 MHz
4. **IPG root clock**: AHB divided by 2 → 66 MHz
5. **PERCLK root clock**: sourced from IPG, divided by 1 → 66 MHz

All clock configuration follows a write-then-wait-for-handshake pattern — after writing divider/mux registers, poll `CCM->CDHIPR` until the corresponding busy bit clears.

## GPIO pin numbering

Pins are numbered 0–31 via `GPIOx_IOxx` macros. Output values use `GPIO_HIGH(x)` = `(1<<x)`, not raw pin numbers.

## Commit style

Commit messages follow the pattern: `【修改描述】【IMX6ULL】<description in Chinese>`
