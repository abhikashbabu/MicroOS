#!/bin/bash

echo "Compiling Micro OS (Modular Architecture)..."

# NAYA: GCC ko saare naye folders ke raste bata diye taaki #include errors na aayein!
INCLUDES="-Isrc/kernel -Isrc/drivers -Isrc/gui -Isrc/runtime -Isrc/fs -Isrc/apps -Isrc"

# 1. Compile Assembly (boot/ folder se)
nasm -f elf32 src/boot/boot.s -o boot.o

# 2. Compile C Files (Sabke naye raste yahan daal diye hain)
gcc -m32 $INCLUDES -c src/drivers/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/apps/shell.c -o shell.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/fs/fs.c -o fs.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/memory.c -o memory.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/task.c -o task.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/drivers/mouse.c -o mouse.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# 3. Link Everything (Sab object files ko jodna)
ld -m elf_i386 -T linker.ld -z noexecstack -o myos.bin boot.o display.o shell.o fs.o memory.o task.o mouse.o kernel.o

echo "Build complete! Running in QEMU..."

# 4. Run Emulator (Tumhara original command + PC Speaker Audio Flag jo humne lagaya tha)
# Run Emulator (Without PulseAudio flags to prevent WSL crash)
qemu-system-i386 -kernel myos.bin -drive format=raw,file=hdd.img,if=ide