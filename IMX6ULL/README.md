## IMX6ULL 裸机驱动

### 目录结构

```
IMX6ULL/
├── Makefile                   ← 顶层入口，make <目录名> 编译指定驱动
├── Common/
│   ├── generic.mk             ← 通用编译规则（自动区分 C / 纯汇编项目）
│   ├── include/
│   │   ├── imx6u.h            ← IMX6ULL 寄存器结构体定义
│   │   └── type.h             ← 标准类型定义
│   ├── lds/
│   │   └── imx6u.lds          ← 公共链接脚本
│   └── src/
│       └── start.s            ← 公共启动文件（SVC 模式 / BSS 清零 / 栈初始化）
└── Driver/
    ├── C_LED/                 ← C 语言 LED 驱动（硬编码寄存器地址）
    ├── STM32_LEDC/            ← C 语言 LED 驱动（公共头文件 + 结构体指针）
    ├── S_LED/                 ← 汇编语言 LED 驱动
    └── SDK_LEDC/              ← 预留
```

### 编译方法

在 `IMX6ULL/` 目录下执行：

```bash
make              # 编译所有驱动
make C_LED        # 编译 Driver/C_LED
make STM32_LEDC   # 编译 Driver/STM32_LEDC
make S_LED        # 编译 Driver/S_LED
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

| 目录 | 语言 | 说明 |
|------|------|------|
| `Driver/S_LED` | 汇编 | GPIO1_IO03 点亮 LED，直接操作寄存器 |
| `Driver/C_LED` | C | GPIO1_IO03 点亮 LED，硬编码寄存器地址宏 |
| `Driver/STM32_LEDC` | C | GPIO1_IO03 点亮 LED，使用公共头文件的结构体指针方式 |
