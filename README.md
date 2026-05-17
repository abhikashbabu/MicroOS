# 🖥️ Micro OS
### 🇮🇳 A Next-Generation Independent Operating System 
**Lightweight. Fast. Yours.**
Micro OS is an experimental, open-source, lightweight operating system built for Intel (x86/x64) architectures. Our ultimate goal is to create a seamless, fast desktop experience featuring a unique `.ind` application ecosystem running on a custom JavaScript runtime.

## 🚀 Features (Planned & Current)
- **Custom MicroKernel:** Written in C and Assembly.
- **VGA Display Driver:** Basic text and graphics rendering.
- **The `.ind` Ecosystem:** Install and run JavaScript-based applications.
- **Micro IDE:** Build and test `.ind` apps directly within the OS.
- **Extremely Lightweight:** Designed to run smoothly on minimal hardware.


## 🛠️ How to Build and Run

### 📦 Prerequisites (Linux / WSL)

First, install the required dependencies:

```bash
sudo apt update
sudo apt install nasm qemu-system-x86 qemu-utils gcc binutils
```

### 🚀 Build and Run the OS

Run the following command:

```bash
./build.sh
```

### 📌 What the Build Script Does

The `build.sh` script typically:

- Compiles the bootloader
- Builds the kernel
- Creates the OS image
- Launches the OS using QEMU emulator



## 🎯 Misson and Vision 
![Micro OS Banner](./mission%20and%20vision.jpg)


## 🤝 Community
We welcome developers of all skill levels! Whether you want to write kernel C code, design the UI, or help build the `.ind` JS runtime, your contributions are valued. Please read our [Contributing Guidelines](CONTRIBUTING.md) to get started.
