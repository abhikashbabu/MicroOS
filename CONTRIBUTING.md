# Contributing to Micro OS

First off, thank you for considering contributing to Micro OS! It's people like you that make open-source awesome.

## 🛠️ Development Workflow

1. **Fork the Repository:** Click the "Fork" button at the top right of this page.
2. **Clone your Fork:** `git clone https://github.com/YOUR_USERNAME/MicroOS.git`
3. **Create a Branch:** `git checkout -b feature/your-feature-name`
4. **Make your Changes:** Write clean, documented code (C/Assembly).
5. **Test in QEMU:** Ensure your changes don't break the boot process. Run `./build.sh`.
6. **Commit your Changes:** `git commit -m "Add some feature"`
7. **Push to your Branch:** `git push origin feature/your-feature-name`
8. **Open a Pull Request:** Go to the original repository and click "Compare & pull request".

## 📝 Coding Standards
* Keep C code modular.
* Comment complex Assembly logic.
* Use descriptive variable names.
