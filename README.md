# My OS
For a lack of name generating skills, I have left the name as ``my-os``. This will stay this way until I, or others, can come up with a fitting name. My-os is an x86_64 only OS that supports both BIOS and UEFI. It is compliant with the [Limine](https://limine-bootloader.org/) protocol.

## Notes
- This really doesn't do much at the moment. There is no userspace, it just simply sets some things up and prints to the screen.

## Dependencies
- You will need to have a cross compiler installed on your system. Currently the build system only supports ``gcc`` compiled to target ``x86_64-elf-gcc``. A guide for building a cross compiler is [here](https://wiki.osdev.org/GCC_Cross-Compiler), provided by [wiki.osdev.org](https://wiki.osdev.org/).

- You also need to have [Qemu](https://www.qemu.org/) installed, specifically ``qemu-system-x86_64``.

- If you wish to view the source code in an editor and are using clangd you might want to generate the compilation database using ``bear -- make clean all``.

## Building
- In the root directory run ``make all``. The Makefile should collect all dependencies, build the kernel and then the disk image. In the future I may make separate commands for building the disk image and the kernel separately.

- In the root directory run ``make clean`` to clean up build files and remove the final disk image.

- In the root directory run ``make run`` to run in qemu.