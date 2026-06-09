# Top-level Makefile for IMX6ULL bare-metal drivers
# Usage:
#   make            — build all tests
#   make <target>   — build a specific test, e.g. make C_LED
#   make clean      — clean all tests
#
# Driver/ 目录为纯 API 库（无 main 函数），不独立构建。
# Test/ 目录为独立外设测试程序（含 main 函数），是唯一的构建目标。
# Common/generic.mk 会自动从 Driver/ 子目录发现并编译所需的库源文件。

TEST_DIR   := Test
TESTS      := $(notdir $(wildcard $(TEST_DIR)/*))

# Common generic makefile (relative to each test directory)
GENERIC_MK := ../../Common/generic.mk

.PHONY: all clean $(TESTS)

all: $(TESTS)

$(TESTS):
	$(MAKE) -C $(TEST_DIR)/$@ -f $(GENERIC_MK)

clean:
	@for d in $(TESTS); do \
		$(MAKE) -C $(TEST_DIR)/$$d -f $(GENERIC_MK) clean; \
	done
	rm -rf *.imx
