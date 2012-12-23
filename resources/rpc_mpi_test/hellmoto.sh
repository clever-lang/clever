#A script to build a shared library to test FFI support on Clever.
gcc -fPIC -O3 -pthread -shared -c hellmoto.c 
gcc -pthread -shared -Wl,-soname,hellmoto.so -o hellmoto.so hellmoto.o -lc -ldl -lpthread


set LD_LIBRARY_PATH=.


