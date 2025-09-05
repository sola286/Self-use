#!/bin/bash
# build.sh - 一键构建脚本

# 确保在项目根目录执行
ROOT_DIR=$(pwd)

# 创建 build/ 目录
mkdir -p build
cd build

# 清理旧文件
echo "清理 build/ 目录..."
rm -rf *

# 重新生成 Makefile
echo "正在运行 cmake .."
cmake -DCMAKE_BUILD_TYPE=Debug ..

# 编译
echo "正在编译项目..."
make -j$(nproc)

echo "构建完成，二进制文件在 bin/ 目录下"

