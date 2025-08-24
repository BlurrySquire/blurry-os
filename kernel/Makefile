GCC	:= x86_64-elf-gcc
G++ := x86_64-elf-g++
AS  := x86_64-elf-gcc
LD 	:= x86_64-elf-ld

C_FLAGS := \
	-Wall \
	-Wextra \
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
	-MMD \
	-MP \
	-Isource

CPP_FLAGS := \
	$(C_FLAGS) \
	-DLIMINE_API_REVISION=3 \

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
CPP_SOURCES := $(wildcard source/*.cpp) $(wildcard source/*/*.cpp)

OBJECTS	     := $(C_SOURCES:source/%.c=build/%.o) $(AS_SOURCES:source/%.S=build/%.o) $(CPP_SOURCES:source/%.cpp=build/%.o)
DEPENDENCIES := $(C_SOURCES:source/%.c=build/%.d) $(CPP_SOURCES:source/%.cpp=build/%.d)

all: $(TARGET)

clean:
	rm -rf build/*

build/%.o: source/%.c
	@mkdir -p $(dir $@)
	@echo "    Compiling $<"
	@$(GCC)	$(C_FLAGS) -std=gnu11 -c $< -o $@

build/%.o: source/%.S
	@mkdir -p $(dir $@)
	@echo "    Compiling $<"
	@$(AS) $(AS_FLAGS) -c $< -o $@

build/%.o: source/%.cpp
	@mkdir -p $(dir $@)
	@echo "    Compiling $<"
	@$(G++) $(CPP_FLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)"
	@$(LD) $(LD_FLAGS) $(OBJECTS) -o $@

-include $(DEPENDENCIES)