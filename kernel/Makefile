GCC	:= x86_64-elf-gcc
AS  := x86_64-elf-as
LD 	:= x86_64-elf-ld

C_FLAGS  := \
	-Wall \
	-Wextra \
	-std=gnu11 \
	-ffreestanding \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fno-PIC \
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel \
	-I../limine

AS_FLAGS := \
	$(C_FLAGS)

LD_FLAGS := \
    -m elf_x86_64 \
    -nostdlib \
    -static \
    -z max-page-size=0x1000 \
    -T linker.ld

TARGET := build/kernel.elf

# Find all the files to compile
C_SOURCES   := $(wildcard source/*.c) $(wildcard source/*/*.c)
AS_SOURCES  := $(wildcard source/*.S) $(wildcard source/*/*.S)
OBJECTS	  := $(C_SOURCES:source/%.c=build/%.o) $(AS_SOURCES:source/%.S=build/%.S)

all: $(TARGET)

clean:
	rm -rf build/*

build/%.o: source/%.c
	@mkdir -p $(dir $@)
	$(GCC)	$(C_FLAGS) -c $< -o $@

build/%.o: source/%.S
	@mkdir -p $(dir $@)
	$(AS) $(AS_FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(LD) $(LD_FLAGS) $(OBJECTS) -o $@