TARGET := blurryos.img
TARGET_DEPS := \
	limine \
	limine.conf \
	kernel/build/kernel.elf

ACTION_SEPARATOR := "===================================="

all: $(TARGET)

$(TARGET): $(TARGET_DEPS)
	@echo "==== MAKING DISK IMAGE ===="
	@./scripts/make_disk.sh
	@echo $(ACTION_SEPARATOR)

kernel/build/kernel.elf: kernel/source/*.* kernel/source/*/*.*
	@echo "==== KERNEL ===="
	@$(MAKE) --no-print-directory -C kernel all
	@echo $(ACTION_SEPARATOR)

limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1
	$(MAKE) -C limine

run:
	@echo "==== RUNNING ===="
	qemu-system-x86_64 \
		-serial stdio \
		-machine type=pc,accel=kvm -m 4096 \
		-drive format=raw,file=$(TARGET),if=none,id=drive0 \
		-device ahci,id=ahci \
		-device ide-hd,drive=drive0,bus=ahci.0
	@echo $(ACTION_SEPARATOR)

clean:
	@echo "==== CLEANING ===="
	$(MAKE) -C kernel clean
	rm -rf $(TARGET)
	@echo $(ACTION_SEPARATOR)