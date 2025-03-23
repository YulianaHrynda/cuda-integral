#!/bin/bash

# зупинити скрипт при помилці
set -e

# === Видаляємо старий білд ===
echo "[1/4] 🔄 Removing old build directory..."
rm -rf build

# === Створюємо новий build ===
echo "[2/4] 🛠️ Creating new build directory..."
mkdir build && cd build

# === Генеруємо CMake проєкт ===
echo "[3/4] ⚙️ Running CMake..."
cmake ..

# === Компілюємо ===
echo "[4/4] 🔨 Building..."
cmake --build .
