TARGET := riscv32-unknown-elf

CC := clang
QEMU := qemu-system-riscv32
OBJCOPY := /usr/bin/llvm-objcopy

BUILD_DIR := build

KERNEL_ELF := $(BUILD_DIR)/kernel.elf
KERNEL_MAP := $(BUILD_DIR)/kernel.map

SHELL_ELF := $(BUILD_DIR)/apps/shell.elf
SHELL_MAP := $(BUILD_DIR)/apps/shell.map
SHELL_BIN := $(BUILD_DIR)/apps/shell.bin
SHELL_BIN_OBJ := $(BUILD_DIR)/apps/shell.bin.o

INCLUDE_DIRS := include

CFLAGS := -std=c11 -O2 -g3 -Wall -Wextra
CFLAGS += --target=$(TARGET)
CFLAGS += $(addprefix -I,$(INCLUDE_DIRS))
CFLAGS += -ffreestanding -fno-stack-protector

LDFLAGS := -fuse-ld=lld -nostdlib
LDFLAGS += --target=$(TARGET)

KERNEL_LDFLAGS := $(LDFLAGS)
KERNEL_LDFLAGS += -Wl,-Tkernel.ld -Wl,-Map=$(KERNEL_MAP)

USER_LDFLAGS := $(LDFLAGS)
USER_LDFLAGS += -Wl,-Tuser.ld -Wl,-Map=$(SHELL_MAP)

KERNEL_SRCS := src/kernel/kernel.c
KERNEL_SRCS += src/kernel/process.c
KERNEL_SRCS += src/kernel/process_test.c
KERNEL_SRCS += src/kernel/scheduler.c
KERNEL_SRCS += src/kernel/virtio.c
KERNEL_SRCS += src/lib/console.c
KERNEL_SRCS += src/lib/string.c
KERNEL_SRCS += src/platform/sbi.c
KERNEL_SRCS += src/mm/page.c


USER_SRCS := src/apps/shell.c
USER_SRCS += src/ulib/user.c
USER_SRCS += src/lib/string.c

KERNEL_OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(KERNEL_SRCS))
USER_OBJS := $(patsubst src/%.c,$(BUILD_DIR)/%.user.o,$(USER_SRCS))

OBJS := $(KERNEL_OBJS) $(USER_OBJS)
DEPS := $(KERNEL_OBJS:.o=.d) $(USER_OBJS:.o=.d)

.PHONY: all run clean

all: $(KERNEL_ELF)

run: $(KERNEL_ELF)
	$(QEMU) -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
			-d unimp,guest_errors,int,cpu_reset -D qemu.log \
			-drive id=drive0,file=lorem.txt,format=raw,if=none \
			-device virtio-blk-device,drive=drive0,bus=virtio-mmio-bus.0 \
			-kernel $(KERNEL_ELF)

clean:
	rm -rf $(BUILD_DIR)

$(KERNEL_ELF): $(KERNEL_OBJS) $(SHELL_BIN_OBJ) kernel.ld | $(BUILD_DIR)
	$(CC) $(KERNEL_LDFLAGS) -o $@ $(KERNEL_OBJS) $(SHELL_BIN_OBJ)

$(SHELL_ELF): $(USER_OBJS) user.ld | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(USER_LDFLAGS) -o $@ $(USER_OBJS)

$(SHELL_BIN): $(SHELL_ELF)
	$(OBJCOPY) --set-section-flags .bss=alloc,contents -O binary $< $@

$(SHELL_BIN_OBJ): $(SHELL_BIN)
	$(OBJCOPY) -I binary -O elf32-littleriscv $< $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.user.o: src/%.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPS)