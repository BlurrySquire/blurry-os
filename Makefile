TARGET := myos.hdd
TARGET_DEPS := \
	kernel/build/kernel.elf \
	limine.conf \
	limine

all: $(TARGET)

$(TARGET): $(TARGET_DEPS)
	./scripts/make_disk.sh

kernel/build/kernel.elf: kernel/source/*.*
	$(MAKE) -C kernel all

run:
	qemu-system-x86_64 \
		-serial stdio \
		-machine type=pc,accel=kvm -m 4096 \
		-drive format=raw,file=$(TARGET)

clean:
	$(MAKE) -C kernel clean
	rm -rf $(TARGET)