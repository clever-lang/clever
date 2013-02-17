#!/bin/bash

echo "Running threads benchmark..."

echo "threads/threads_001.clv:"
../clever threads/threads_001.clv
echo "[OK]"

echo "threads/threads_001.py: [python version]"
python threads/threads_001.py
echo "[OK]"

echo "threads/threads_001.php: [php version]"
php threads/threads_001.php
echo "[OK]"

