#! /bin/bash

TARGET=blurryos.hdd
SIZE_MB=128

# Create an empty disk image
dd if=/dev/zero bs=1M count=$SIZE_MB of=$TARGET

# Partition the disk
sgdisk $TARGET\
    -n 1:2048:+64M -t 1:ef00 -c 1:"EFI System" \
    -n 2:0:0 -t 2:0700 -c 2:"MyOS Data"

# Figure out the offsets for each partition
SECTOR_SIZE=512
PART1_SECTOR=$(sgdisk -i 1 "$TARGET" | grep 'First sector' | awk '{print $3}')
PART2_SECTOR=$(sgdisk -i 2 "$TARGET" | grep 'First sector' | awk '{print $3}')

PART1_OFFSET=$(($PART1_SECTOR * $SECTOR_SIZE))
PART2_OFFSET=$(($PART2_SECTOR * $SECTOR_SIZE))

./limine/limine bios-install $TARGET

mformat -F -i $TARGET@@$PART1_OFFSET
mmd -i $TARGET@@$PART1_OFFSET ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine
mcopy -i $TARGET@@$PART1_OFFSET kernel/build/kernel.elf ::/boot
mcopy -i $TARGET@@$PART1_OFFSET limine.conf limine/limine-bios.sys ::/boot/limine
mcopy -i $TARGET@@$PART1_OFFSET limine/BOOTX64.EFI ::/EFI/BOOT