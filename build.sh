#!/bin/bash

# --- 環境變數設定 (選用) ---
# 如果你是使用 sudo apt install gcc-aarch64-linux-gnu 安裝的，這行通常不需要
# 如果你是用自己下載的工具鏈，請解除下面這行的註解並修改路徑
# export PATH=/opt/arm/gcc-linaro-aarch64-none-elf-4.9-2014.09_linux/bin/:$PATH

echo "========================================"
echo "  Starting Multi-Platform Build System"
echo "========================================"

# 1. 編譯 Ubuntu 版本
echo "[1/2] Building for Ubuntu (x86_64)..."
make PLATFORM=ubuntu clean
make PLATFORM=ubuntu -j$(nproc)
if [ $? -eq 0 ]; then
    echo "Done: ModuleTest_ubuntu created."
else
    echo "Error: Ubuntu build failed!"
    exit 1
fi

echo ""

# 2. 編譯 Raspberry Pi 4B 版本
echo "[2/2] Building for Raspberry Pi 4B (AArch64)..."
make PLATFORM=rpi clean
make PLATFORM=rpi -j$(nproc)
if [ $? -eq 0 ]; then
    echo "Done: ModuleTest_rpi created."
else
    echo "Error: Raspberry Pi build failed! (Check if gcc-aarch64-linux-gnu is installed)"
    exit 1
fi

echo ""
echo "========================================"
echo "  All Builds Finished Successfully!"
echo "========================================"
ls -F ModuleTest_*