#!/bin/bash

echo "Compiling Micro OS..."

# Compile Assembly
nasm -f elf32 src/boot.s -o boot.o

# Compile C Files (Kernel & Display)
gcc -m32 -c src/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Link Everything
ld -m elf_i386 -T linker.ld -o myos.bin boot.o display.o kernel.o

echo "Build complete! Running in QEMU..."

# Run Emulator
qemu-system-i386 -kernel myos.bin