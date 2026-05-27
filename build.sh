#!/bin/bash
set -e 

echo "Compiling Micro OS (Modular Architecture)..."

INCLUDES="-Isrc/kernel -Isrc/drivers -Isrc/gui -Isrc/runtime -Isrc/fs -Isrc/apps -Isrc/boot"

nasm -f elf32 src/boot/boot.s -o boot.o

gcc -m32 $INCLUDES -c src/drivers/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/apps/shell.c      -o shell.o   -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/fs/fs.c           -o fs.o      -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/memory.c   -o memory.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/task.c     -o task.o    -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/drivers/mouse.c   -o mouse.o   -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/kernel.c   -o kernel.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra

ld -m elf_i386 -T linker.ld -z noexecstack -o myos.bin boot.o display.o shell.o fs.o memory.o task.o mouse.o kernel.o

echo "Build complete! Booting in QEMU..."
qemu-system-i386 -kernel myos.bin -drive format=raw,file=hdd.img,if=ide