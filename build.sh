#!/bin/bash

echo "Compiling Micro OS..."

# Compile Assembly
nasm -f elf32 src/boot.s -o boot.o

# Compile C Files (Yahan memory.c add kiya hai)
gcc -m32 -c src/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/shell.c -o shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/fs.c -o fs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/memory.c -o memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Link Everything (Yahan memory.o add kiya hai)
ld -m elf_i386 -T linker.ld -z noexecstack -o myos.bin boot.o display.o shell.o fs.o memory.o kernel.o

echo "Build complete! Running in QEMU..."

# Run Emulator (Hard drive ke sath)
qemu-system-i386 -kernel myos.bin -drive format=raw,file=hdd.img,if=ide