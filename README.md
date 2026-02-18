# Interactive Command-Based Test Application

## Overview
This project is an **interactive command-based test application** written in C. It supports multi-platform execution, allowing you to run the same codebase on both a local Ubuntu machine and a Raspberry Pi 4B (ARM64).


## Features
- Multi-platform support: **Ubuntu (x86_64)** and **Raspberry Pi 4B (AArch64)**.
- Interactive command-line interface with extensible command table.
- Modular design: Math operations, system info, and Linux environment tests.
- Support for both Desktop and Embedded testing modes.


## Build Information
- **Author:** Louis Wang  
- **Date:** 2026-02-18  
- **Versioning:** Managed via `version.h`  
- **Platforms:** Ubuntu (Native), Raspberry Pi 4B (Cross-compiled)


## Build & Installation

### 1. Prerequisites (For Cross-Compilation)
If you want to build for Raspberry Pi 4B on your Ubuntu machine, you must install the ARM64 cross-compiler:

```bash
sudo apt update
sudo apt install gcc-aarch64-linux-gnu
```

### 2. Fast Build (Using Shell Script)

We provide a `build.sh` to compile both platforms at once:

```bash
chmod +x build.sh
./build.sh
```

This will generate:

* `ModuleTest_ubuntu`: Executable for your PC.
* `ModuleTest_rpi`: Executable for Raspberry Pi 4B.

### 3. Manual Build (Using Makefile)

You can build for a specific platform using the `PLATFORM` variable:

* **For Ubuntu:**
```bash
make PLATFORM=ubuntu clean
make PLATFORM=ubuntu
```


* **For Raspberry Pi 4B:**
```bash
make PLATFORM=rpi clean
make PLATFORM=rpi
```

## Deployment to Raspberry Pi

1. **Transfer the binary to RPi:**
```bash
scp ./ModuleTest_rpi pi@<your_rpi_ip>:~/
```


2. **Run on RPi:**
```bash
ssh pi@<your_rpi_ip>
chmod +x ModuleTest_rpi
./ModuleTest_rpi
```

## Command Table

| Command | Description | Example |
| --- | --- | --- |
| `.HELP` | Show available commands | `.HELP` |
| `.MATH` | Perform math operations (a + b, a*b) | `.MATH 10 20` |
| `.TEST` | Run internal module logic validation | `.TEST` |
| `.LS` | List files in current directory (RPi) | `.LS` |
| `.INFO` | Show build date and version | `.INFO` |
| `.EXIT` | Terminate the application | `.EXIT` |


## Project Structure

* `main.c`: Core logic, command dispatcher, and UI loop.
* `test/math/`: Math utility functions and handlers.
* `test/sample/`: Sample test modules.
* `include/`: Common definitions and versioning.
* `Makefile`: Multi-platform build system.
* `build.sh`: Automation script for dual-platform release.

## Author

Louis Wang