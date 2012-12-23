#A script to build a shared library to test FFI support on Clever.
gcc -fPIC -O3 -shared -c gmp.c
gcc -shared -Wl,-soname,gmp.so -o gmp.so gmp.o -lc -ldl -lgmp


set LD_LIBRARY_PATH=.

./clever  gmp.clv

