#!/bin/bash

echo "Running threads benchmark..."

echo "threads/threads_001.clv:"
../clever threads/threads_001.clv
echo "[OK]"

echo "threads/threads_001.py: [python version]"
python threads/threads_001.py
echo "[OK]"

echo "threads/threads_001.lua: [lua version]"
lua threads/threads_001.lua
echo "[OK]"

echo "threads/threads_001.php: [php version]"
php threads/threads_001.php
echo "[OK]"

echo "threads/threads_001.rb: [ruby version]"
ruby threads/threads_001.rb
echo "[OK]"

echo "threads/threads_001.c: [C version]"
gcc -O2 -o threads/threads_001.exe threads/threads_001.c
threads/threads_001.exe
echo "[OK]"

