TARGET := riscv32-unknown-elf

CC := clang
QEMU := qemu-system-riscv32

BUILD_DIR := build
KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_MAP := $(BUILD_DIR)/kernel.map
INCLUDE_DIRS := include

CFLAGS := -std=c11 -O2 -g3 -Wall -Wextra
CFLAGS += --target=$(TARGET)
CFLAGS += $(addprefix -I,$(INCLUDE_DIRS))
CFLAGS += -ffreestanding -fno-stack-protector

LDFLAGS := -fuse-ld=lld -nostdlib
LDFLAGS += --target=$(TARGET)
LDFLAGS += -Wl,-Tkernel.ld -Wl,-Map=$(KERNEL_MAP)

SRCS := src/kernel/kernel.c src/lib/console.c src/lib/string.c src/platform/sbi.c
OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all run clean

all: $(KERNEL_ELF)

run: $(KERNEL_ELF)
	$(QEMU) -machine virt -bios default -nographic -serial mon:stdio \
		--no-reboot -kernel $(KERNEL_ELF)

clean:
	rm -rf $(BUILD_DIR)

$(KERNEL_ELF): $(OBJS) kernel.ld | $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)
