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
make C_LED LINK_ADDR=0x87800000          # Change link address
make C_LED TARGET=myapp                  # Change output binary name
```

Default toolchain: `arm-linux-gnueabihf-`. Build produces `.elf`, `.bin`, and `.dis` (disassembly) files in each test directory.

## Architecture

Three-layer separation:

1. **`Common/`** — Chip-level infrastructure shared by everything. Startup code (`start.s`), link script (`imx6u.lds`), NXP SDK headers (`MCIMX6Y2.h`, `fsl_common.h`, `fsl_iomuxc.h`), self-built register structs (`imx6u.h`), and the build system (`generic.mk`).

2. **`Driver/`** — Reusable peripheral driver API libraries. Each subdirectory is a self-contained driver (GPIO, Delay, Beep, Key, LED). These have **no `main()` function** — they are pure libraries compiled into tests automatically by `generic.mk`.

3. **`Test/`** — Standalone test programs, each with a `main()` function. One subdirectory per test. New test directories need only source files — no Makefile required. `generic.mk` auto-detects C vs. assembly projects and sets up the build accordingly.

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

`GPIO_Type`, `CCM_Type`, etc. are defined in `imx6u.h` as structs with `volatile uint32_t` fields, then cast to base addresses via macros like `#define GPIO1 ((GPIO_Type *)0x0209C000)`.

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

The `CCGRx_VALUE` macro and `IOMUXC_SetPinMux`/`IOMUXC_SetPinConfig` from the NXP SDK are the standard way to perform clock and pin setup.

## GPIO pin numbering

Pins are numbered 0–31 via `GPIOx_IOxx` macros. Output values use `GPIO_HIGH(x)` = `(1<<x)`, not raw pin numbers.

## Commit style

Commit messages follow the pattern: `【修改描述】【IMX6ULL】<description in Chinese>`
