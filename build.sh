#!/bin/bash

echo "Compiling Micro OS..."

# Compile Assembly
nasm -f elf32 src/boot.s -o boot.o

# Compile C Files
gcc -m32 -c src/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/shell.c -o shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Link Everything (Notice shell.o added here)
# Link Everything (Warning hatane ke liye update kiya gaya)
ld -m elf_i386 -T linker.ld -z noexecstack -o myos.bin boot.o display.o shell.o kernel.o
echo "Build complete! Running in QEMU..."

# Run Emulator
qemu-system-i386 -kernel myos.bin