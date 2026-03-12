#!/bin/bash

echo "Building UAF Lab..."

# Build with ASan for challenges 01-07
gcc -fsanitize=address -g -o uaf_01 uaf_01_basic.c
gcc -fsanitize=address -g -o uaf_02 uaf_02_double_free.c
gcc -fsanitize=address -g -o uaf_03 uaf_03_buffer_overflow.c
gcc -fsanitize=address -g -o uaf_04 uaf_04_dangling_pointer.c
gcc -fsanitize=address -g -o uaf_05 uaf_05_struct.c
gcc -fsanitize=address -g -o uaf_06 uaf_06_fixed.c
gcc -fsanitize=address -g -o uaf_07 uaf_07_heap_spray.c

# Build CTF challenge without ASan (to keep vulnerabilities)
gcc -o uaf_08 uaf_08_ctf.c

echo "Build complete!"
echo ""
echo "Usage:"
echo "  ./uaf_01 to ./uaf_07 - Run with AddressSanitizer"
echo "  ./uaf_08 - CTF Challenge (no ASan)"
