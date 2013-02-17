#!/bin/bash

echo "Running threads benchmark..."

cd threads
echo "threads/threads_001.clv:"
../../clever threads_001.clv
echo "[OK]"

echo "threads/threads_001.py: [python version]"
python threads_001.py
echo "[OK]"

echo "threads/threads_001.lua: [lua version]"
lua threads_001.lua
echo "[OK]"

echo "threads/threads_001.php: [php version]"
php threads_001.php
echo "[OK]"

echo "threads/threads_001.rb: [ruby version]"
ruby threads/threads_001.rb
echo "[OK]"

echo "threads/threads_001.c: [C version]"
gcc -O2 -o threads_001.exe threads_001.c
./threads_001.exe
echo "[OK]"

echo "threads/threads_001.java: [Java version]"
javac threads_001.java
java threads_001

