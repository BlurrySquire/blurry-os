TARGET := blurryos.hdd
TARGET_DEPS := \
	limine \
	limine.conf \
	kernel/build/kernel.elf

all: $(TARGET)

$(TARGET): $(TARGET_DEPS)
	./scripts/make_disk.sh

# Build kernel dependency
kernel/build/kernel.elf: kernel/source/*.* kernel/source/*/*.*
	$(MAKE) -C kernel all

# Get limine dependency
limine:
	git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1
	$(MAKE) -C limine

run:
	qemu-system-x86_64 \
		-serial stdio \
		-machine type=pc,accel=kvm -m 4096 \
		-drive format=raw,file=$(TARGET),if=none,id=drive0 \
		-device ahci,id=ahci \
		-device ide-hd,drive=drive0,bus=ahci.0

clean:
	$(MAKE) -C kernel clean
	rm -rf $(TARGET)