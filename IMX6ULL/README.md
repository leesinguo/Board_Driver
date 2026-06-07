## IMX6ULL 裸机驱动

### 目录结构

```
IMX6ULL/
├── Makefile                   ← 顶层入口，make <目录名> 编译指定驱动
├── Common/
│   ├── generic.mk             ← 通用编译规则（自动区分 C / 纯汇编项目）
│   ├── include/
│   │   ├── MCIMX6Y2.h         ← NXP 官方 MCIMX6Y2 全寄存器定义
│   │   ├── fsl_common.h       ← NXP SDK 公共定义（状态码、版本号、断言等）
│   │   ├── fsl_iomuxc.h       ← NXP SDK IOMUXC 引脚复用驱动
│   │   ├── imx6u.h            ← 自建寄存器结构体定义
│   │   └── type.h             ← 标准类型定义（含 NXP SDK 风格 s8/u8/__IO 等）
│   ├── lds/
│   │   └── imx6u.lds          ← 公共链接脚本
│   └── src/
│       └── start.s            ← 公共启动文件（SVC 模式 / BSS 清零 / 栈初始化）
└── Driver/
    ├── C_LED/                 ← C 语言 LED 驱动（硬编码寄存器地址）
    ├── STM32_LEDC/            ← C 语言 LED 驱动（公共头文件 + 结构体指针）
    ├── SDK_LEDC/              ← C 语言 LED 驱动（NXP 官方 SDK 方式）
    ├── S_LED/                 ← 汇编语言 LED 驱动
    └── Beep/                  ← C 语言蜂鸣器驱动（NXP 官方 SDK 方式）
```

### 编译方法

在 `IMX6ULL/` 目录下执行：

```bash
make              # 编译所有驱动
make C_LED        # 编译 Driver/C_LED
make STM32_LEDC   # 编译 Driver/STM32_LEDC
make S_LED        # 编译 Driver/S_LED
make SDK_LEDC     # 编译 Driver/SDK_LEDC
make Beep         # 编译 Driver/Beep
make clean        # 清理所有驱动
```

可覆盖变量：

```bash
make C_LED TARGET=myapp              # 指定输出文件名
make C_LED LINK_ADDR=0x80000000      # 指定链接地址（默认 0x87800000）
make C_LED CROSS_COMPILE=arm-none-eabi-  # 指定交叉编译器前缀
```

新增驱动目录只需放入源码文件，无需编写 Makefile。`Common/generic.mk` 会自动检测项目类型：
- 目录包含 `.c` 文件 → C 模式：自动引入公共启动文件、链接脚本、头文件
- 目录仅 `.s` 文件 → 汇编模式：仅编译本地汇编文件，`-Ttext` 直接链接

### 驱动列表

| 目录 | 语言 | 寄存器访问方式 | 说明 |
|------|------|----------------|------|
| `Driver/S_LED` | 汇编 | 硬编码地址 | GPIO1_IO03 点亮 LED，纯汇编实现 |
| `Driver/C_LED` | C | 硬编码地址宏 | GPIO1_IO03 点亮 LED，自建宏定义 |
| `Driver/STM32_LEDC` | C | 自建结构体指针 | GPIO1_IO03 点亮 LED，imx6u.h 结构体方式 |
| `Driver/SDK_LEDC` | C | NXP SDK | GPIO1_IO03 点亮 LED，移植 NXP 官方 SDK |
| `Driver/Beep` | C | NXP SDK | GPIO5_IO01 驱动蜂鸣器，移植 NXP 官方 SDK |

### NXP SDK 移植说明

移植自 NXP MCUXpresso SDK，包含以下文件：

| 文件 | 来源 | 说明 |
|------|------|------|
| `Common/include/MCIMX6Y2.h` | NXP SDK `devices/MCIMX6Y2/MCIMX6Y2.h` | 芯片全寄存器映射，42000+ 行 |
| `Common/include/fsl_common.h` | NXP SDK `components/serial_manager/fsl_common.h` | SDK 公共宏定义与工具函数 |
| `Common/include/fsl_iomuxc.h` | NXP SDK `drivers/fsl_iomuxc.h` | IOMUXC 引脚复用驱动，含全部引脚功能 ID |

`type.h` 同步增加了 NXP SDK 依赖的类型定义：
- `s8/s16/s32/s64`、`u8/u16/u32/u64` — NXP SDK 标准整数类型
- `__I` / `__O` / `__IO` — 寄存器 volatile 访问修饰
