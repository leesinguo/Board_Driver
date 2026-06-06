# Top-level Makefile for IMX6ULL bare-metal drivers
# Usage:
#   make            — build all drivers
#   make <target>   — build a specific driver, e.g. make C_LED
#   make clean      — clean all drivers

DRIVER_DIR := Driver
DRIVERS    := $(notdir $(wildcard $(DRIVER_DIR)/*))

# Common generic makefile (relative to each driver directory)
GENERIC_MK := ../../Common/generic.mk

.PHONY: all clean $(DRIVERS)

all: $(DRIVERS)

$(DRIVERS):
	$(MAKE) -C $(DRIVER_DIR)/$@ -f $(GENERIC_MK)

clean:
	@for d in $(DRIVERS); do \
		$(MAKE) -C $(DRIVER_DIR)/$$d -f $(GENERIC_MK) clean; \
	done
