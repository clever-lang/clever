cd tests/std.ffi/
rm -f *.o *.so
gcc -fPIC -O3 -shared -c ffi_001.c
gcc -shared -Wl,-soname,ffi_001.so -o ffi_001.so ffi_001.o -lc -ldl
LD_LIBRARY_PATH=.

