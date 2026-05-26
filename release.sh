#!/bin/bash

# Make sure we have the latest build
echo "Building final release version..."
./build.sh

# Create the release directory
mkdir -p MicroOS_v3.0_Release

# Copy the core OS files
echo "Packaging OS files..."
cp myos.bin MicroOS_v3.0_Release/
cp hdd.img MicroOS_v3.0_Release/

# Create a clean README for GitHub users
echo "Generating README..."
cat << 'EOF' > MicroOS_v3.0_Release/README.md
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
EOF

# Zip everything up!
echo "Zipping Release..."
cd MicroOS_v3.0_Release
zip -r ../MicroOS_v3.0_Release.zip *
cd ..

echo ""
echo "=================================================="
echo "SUCCESS! MicroOS_v3.0_Release.zip is ready!"
echo "Upload this ZIP file to your GitHub Releases page!"
echo "=================================================="