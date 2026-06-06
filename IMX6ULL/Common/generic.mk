# Common Makefile for IMX6ULL bare-metal drivers
# Usage from project root:  make <dir>
# Or manually from driver dir:  make -f ../../Common/generic.mk
#
# Overridable variables:
#   make TARGET=xxx          — specify output name (default: current dir name)
#   make LINK_ADDR=0x......  — specify link address (default: 0x87800000)
#   make CROSS_COMPILE=xxx-  — specify cross-compiler prefix

CROSS_COMPILE ?= arm-linux-gnueabihf-
LINK_ADDR    ?= 0x87800000
TARGET       ?= $(notdir $(CURDIR))

# ---------- auto-discover source files ----------
ASM_SRCS := $(wildcard *.s)
C_SRCS   := $(wildcard *.c)

# ---------- auto-detect project type ----------
# C project: use common infrastructure (startup, linker script, headers)
# ASM-only: standalone, no common dependencies
ifneq ($(C_SRCS),)
VPATH           := ../../Common/src
COMMON_ASM_SRCS := $(notdir $(wildcard ../../Common/src/*.s))
INCLUDES        := -I../../Common/include
LINK_SCRIPT     := $(or $(wildcard *.lds), $(wildcard ../../Common/lds/*.lds))
else
COMMON_ASM_SRCS :=
INCLUDES        :=
LINK_SCRIPT     := $(wildcard *.lds)
endif

OBJS := $(ASM_SRCS:.s=.o) $(COMMON_ASM_SRCS:.s=.o) $(C_SRCS:.c=.o)
DEPS := $(C_SRCS:.c=.d)

# ---------- toolchain ----------
AS      = $(CROSS_COMPILE)gcc
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# ---------- flags ----------
ASFLAGS = -g -c -O2
CFLAGS  = -g -c -Wall -MMD -O2 $(INCLUDES)

# Linker flags: use linker script if present, otherwise fall back to -Ttext
ifneq ($(LINK_SCRIPT),)
LDFLAGS := -T $(LINK_SCRIPT)
else
LDFLAGS := -Ttext $(LINK_ADDR)
endif

# ---------- targets ----------
.PHONY: all clean

all: $(TARGET).bin

$(TARGET).bin: $(OBJS) $(LINK_SCRIPT)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET).elf
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D $(TARGET).elf > $(TARGET).dis

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.elf *.bin *.dis *.imx *.d

-include $(DEPS)
