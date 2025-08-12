# The Plan

## File structure

### Boot Partition
- Marked as EFI System Partition.
- Fat32 because UEFI demands it.
- Contains the legacy BIOS boot sector.
- Contains Limine boot stages.
- Contains Limine config file.
- Contains the kernel binary.
- Contains driver modules.

### Root Partition
- Contains all system files.
- ``/boot`` mount point of the boot partition.
- ``/devices`` contains "files" for interacting with devices.
- ``/config`` contains configuration files which I don't currently have a use for.