#!/bin/bash

echo "Compiling Micro OS..."

# Compile Assembly
nasm -f elf32 src/boot.s -o boot.o

# Compile C Files (Yahan mouse.c add kiya)
gcc -m32 -c src/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/shell.c -o shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/fs.c -o fs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/memory.c -o memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/task.c -o task.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/mouse.c -o mouse.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 -c src/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Link Everything (Yahan mouse.o add kiya)
ld -m elf_i386 -T linker.ld -z noexecstack -o myos.bin boot.o display.o shell.o fs.o memory.o task.o mouse.o kernel.o

echo "Build complete! Running in QEMU..."

# Run Emulator
qemu-system-i386 -kernel myos.bin -drive format=raw,file=hdd.img,if=ide