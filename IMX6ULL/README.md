## IMX6ULL 裸机驱动

### 设计理念

项目采用三层分离架构：

- **Common/** — 芯片级通用基础设施（寄存器定义、启动文件、链接脚本、编译规则）
- **Driver/** — 各外设的 API 接口库（无 `main` 函数，提供可复用的驱动函数）
- **Test/** — 独立的外设测试程序（含 `main` 函数，调用 Driver API，可直接编译运行）

`Common/generic.mk` 在 C 模式下会自动扫描并编译 `Driver/` 下所有 `.c` 库文件，
测试程序无需显式列出依赖的库。

### 目录结构

```
IMX6ULL/
├── Makefile                   ← 顶层入口，make <目录名> 编译指定测试目标
├── Common/
│   ├── generic.mk             ← 通用编译规则（自动发现 Driver 库 + 区分 C/汇编项目）
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
├── Driver/                    ← 驱动 API 接口库（纯库，无 main 函数）
│   ├── GPIO/
│   │   ├── gpio.c             ← GPIO 操作 API（初始化、读写、方向配置）
│   │   └── gpio.h
│   ├── Delay/
│   │   ├── delay.c            ← 延时函数 API（毫秒延时、短延时）
│   │   └── delay.h
│   ├── Beep/
│   │   ├── Beep.c             ← 蜂鸣器 API（初始化、开关控制）
│   │   └── Beep.h
│   └── Key/
│       ├── Key.c              ← 按键 API（初始化、消抖读取）+ LED 控制 API
│       └── Key.h
└── Test/                      ← 独立外设测试程序（含 main 函数）
    ├── C_LED/                 ← C 语言 LED 测试（硬编码寄存器地址）
    ├── STM32_LEDC/            ← C 语言 LED 测试（公共头文件 + 结构体指针）
    ├── SDK_LEDC/              ← C 语言 LED 测试（NXP 官方 SDK 方式）
    ├── S_LED/                 ← 汇编语言 LED 测试
    ├── Beep/                  ← 蜂鸣器测试（调用 Driver/Beep API）
    └── Key/                   ← 按键测试（调用 Driver/Key + Driver/Beep API）
```

### 编译方法

在 `IMX6ULL/` 目录下执行：

```bash
make              # 编译所有测试程序
make C_LED        # 编译 Test/C_LED
make STM32_LEDC   # 编译 Test/STM32_LEDC
make S_LED        # 编译 Test/S_LED
make SDK_LEDC     # 编译 Test/SDK_LEDC
make Beep         # 编译 Test/Beep
make Key          # 编译 Test/Key
make clean        # 清理所有测试程序
```

可覆盖变量：

```bash
make C_LED TARGET=myapp              # 指定输出文件名
make C_LED LINK_ADDR=0x80000000      # 指定链接地址（默认 0x87800000）
make C_LED CROSS_COMPILE=arm-none-eabi-  # 指定交叉编译器前缀
```

新增测试目录只需放入源码文件，无需编写 Makefile。`Common/generic.mk` 会自动：
- 检测项目类型（C 或纯汇编）
- C 模式：自动引入公共启动文件、链接脚本、Common 头文件
- C 模式：自动扫描 `Driver/` 下所有 `.c` 库文件并编译链接
- 汇编模式：仅编译本地汇编文件，`-Ttext` 直接链接

驱动 API 接口放入 `Driver/` 子目录，独立外设测试程序放入 `Test/` 子目录。

### 驱动 API 列表

| 目录 | API 函数 | 说明 |
|------|----------|------|
| `Driver/GPIO` | `gpio_init()`, `gpio_pin_write()`, `gpio_pin_read()` | GPIO 初始化、读写、方向配置 |
| `Driver/Delay` | `delay()`, `delay_short()` | 毫秒延时、短延时 |
| `Driver/Beep` | `beep_init()`, `beep_switch()` | 蜂鸣器初始化、开关控制 |
| `Driver/Key` | `key_init()`, `key_getvalue()`, `led_init()`, `led_switch()` | 按键初始化/消抖读取、LED 初始化/控制 |

### 测试列表

| 目录 | 语言 | 寄存器访问方式 | 说明 |
|------|------|----------------|------|
| `Test/S_LED` | 汇编 | 硬编码地址 | GPIO1_IO03 点亮 LED，纯汇编实现 |
| `Test/C_LED` | C | 硬编码地址宏 | GPIO1_IO03 点亮 LED，自建宏定义 |
| `Test/STM32_LEDC` | C | 自建结构体指针 | GPIO1_IO03 点亮 LED，imx6u.h 结构体方式 |
| `Test/SDK_LEDC` | C | NXP SDK | GPIO1_IO03 点亮 LED，移植 NXP 官方 SDK |
| `Test/Beep` | C | NXP SDK | GPIO5_IO01 驱动蜂鸣器，调用 Driver/Beep API |
| `Test/Key` | C | NXP SDK | 按键 + LED + 蜂鸣器综合测试，调用 Driver API |

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

### 蜂鸣器驱动说明

`Driver/Beep` 是基于 NXP 官方 SDK 实现的蜂鸣器驱动 API，演示了如何通过 SDK API 驱动不同于 LED 的外设。

**API 用法：**

```c
#include "Beep.h"

beep_init();           // 初始化蜂鸣器（时钟 + 引脚复用 + GPIO 方向）
beep_switch(1);        // 打开蜂鸣器
beep_switch(0);        // 关闭蜂鸣器
```

**引脚配置：**

| 项目 | 值 |
|------|-----|
| 引脚 | SNVS_TAMPER1 |
| 复用功能 | GPIO5_IO01 |
| 方向 | 输出 |
| 有效电平 | 低电平（蜂鸣器响） |
| PAD 属性 | 0x10B0 |

**驱动流程：**

```
使能时钟 (CCM CCGR0~6) → 配置引脚复用 (IOMUXC) → 设置 GPIO 方向 → 输出低/高电平
```

**SDK 外设调用对比：**

与 `Test/SDK_LEDC`（GPIO1_IO03）相比，本驱动展示了 NXP SDK 在不同 GPIO 端口上的复用模式：

| 对比项 | SDK_LEDC | Beep |
|--------|----------|------|
| GPIO 端口 | GPIO1 | GPIO5 |
| 引脚 | GPIO1_IO03 | GPIO5_IO01 |
| IOMUXC 宏 | `IOMUXC_GPIO1_IO03_GPIO1_IO03` | `IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01` |
| 方向寄存器 | `GPIO1->GDIR` | `GPIO5->GDIR` |
| 数据寄存器 | `GPIO1->DR` | `GPIO5->DR` |
| 输出电平 | 高电平（LED 亮） | 低电平（蜂鸣器响） |
