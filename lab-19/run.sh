#!/usr/bin/env bash
# Одна команда: собери и запусти банкомат
set -e
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$SCRIPT_DIR"

if ! command -v cmake &>/dev/null; then
  echo "[ERR] cmake не найден. Установи: sudo apt install cmake build-essential"
  exit 1
fi

cmake -B build -DCMAKE_BUILD_TYPE=Release -DATM_BUILD_TESTS=OFF -Wno-dev > /dev/null 2>&1
cmake --build build --target atm -j"$(nproc)" > /dev/null 2>&1
exec ./build/atm
