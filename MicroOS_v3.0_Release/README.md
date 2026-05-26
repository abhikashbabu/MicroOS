# Micro OS v3.0 (GitHub Release)
Created by Abhikash (100 Days of OS Dev Challenge)

## Features:
- Complete Custom GUI Environment
- Real-time Hardware Clock & CMOS Access
- 13 Built-in Apps (Paint, Calculator, Tic-Tac-Toe, Piano Synth, File Explorer)
- Custom `.IND` Interpreter Support
- Disk Management & VRAM Serialization (Image Saving)

## How to run:
Use QEMU to boot this OS. Make sure you attach the hard drive image!
`qemu-system-i386 -kernel myos.bin -drive file=hdd.img,format=raw -audiodev pa,id=snd0 -machine pcspk-audiodev=snd0`
