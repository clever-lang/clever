#A script to build a shared library to test FFI support on Clever.
gcc -fPIC -O3 -shared -c nffi.c
gcc -shared -Wl,-soname,nffi.so -o nffi.so nffi.o -lc -ldl

LD_LIBRARY_PATH=.

valgrind --tool=helgrind ../../clever  nffi.clv
valgrind  ../../clever nffi2.clv


rm -f *.o *~ *.so
