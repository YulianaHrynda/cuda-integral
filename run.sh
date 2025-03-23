#!/bin/bash

set -e

echo "[1/4] 🔄 Removing old build directory..."
rm -rf build

echo "[2/4] 🛠️ Creating new build directory..."
mkdir build && cd build

echo "[3/4] ⚙️ Running CMake..."
cmake ..

echo "[4/4] 🔨 Building..."
cmake --build .
