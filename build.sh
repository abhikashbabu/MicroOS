#!/bin/bash
set -e 

echo "Compiling Micro OS (Day 107 Smart Fallback & VESA)..."

INCLUDES="-Isrc/kernel -Isrc/drivers -Isrc/gui -Isrc/runtime -Isrc/fs -Isrc/apps -Isrc/boot"

# 1. Compile Assembly
nasm -f elf32 src/boot/boot.s -o boot.o
# Compile the ISR Assembly wrappers
nasm -f elf32 src/kernel/isr.asm -o src/kernel/isr.o

# 2. Compile C Files
gcc -m32 $INCLUDES -c src/drivers/display.c -o display.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/apps/shell.c      -o shell.o   -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/fs/fs.c           -o fs.o      -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/memory.c   -o memory.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/task.c     -o task.o    -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/drivers/mouse.c   -o mouse.o   -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc -m32 $INCLUDES -c src/kernel/kernel.c   -o kernel.o  -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# 3. YAHAN THI GALTI! Ab hum wapas SAARI files ko link kar rahe hain
ld -m elf_i386 -T linker.ld -z noexecstack -o myos.bin boot.o display.o shell.o fs.o memory.o task.o mouse.o kernel.o src/kernel/isr.o

echo "Packaging OS into Bootable ISO..."
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin

cat > isodir/boot/grub/grub.cfg << EOF
set timeout=2
set default=0
menuentry "Micro OS v3.0 (Smart Fallback Mode)" {
    multiboot /boot/myos.bin
    boot
}
EOF

grub-mkrescue -o microos.iso isodir
echo "Booting ISO in QEMU..."

# NAYA FIX: Yahan humne QEMU ko RTL8139 Network Card lagane ka order de diya hai
qemu-system-i386 -cdrom microos.iso -drive format=raw,file=hdd.img,if=ide -vga std -net nic,model=rtl8139 -net user -boot d