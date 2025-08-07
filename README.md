# Blurry OS
Blurry OS is a 64-bit OS currently targeting x86_64. There are plans to potentially support other 64-bit architectures in the future. It makes use of the [Limine bootloader](https://limine-bootloader.org/) for booting via BIOS and UEFI. At the moment Blurry OS is quite minimal. It just boots the system and sets up some stuff.

## Dependencies
- You will need to have a cross compiler installed on your system. Currently the build system only supports ``gcc`` compiled to target ``x86_64-elf-gcc``. A guide for building a cross compiler is [here](https://wiki.osdev.org/GCC_Cross-Compiler), from the OS dev wiki.

- You also need to have [Qemu](https://www.qemu.org/) installed for targeting x86_64.

- If you use clangd then you need to have [bear](https://github.com/rizsotto/Bear) installed and run the command ``bear -- make clean all`` to generate the compilation database.

## Building
- In the root directory run the command ``make all`` to start the build process. If you just ran the bear command before then it might already be built.

- You can also run Blurry OS in qemu by running ``make run``.

- You can also clean all build files by using ``make clean``.