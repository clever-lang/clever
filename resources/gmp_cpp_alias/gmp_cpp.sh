#A script to build a shared library to test FFI support on Clever.
g++ -fPIC -O3 -shared -c gmp.cpp
g++ -shared -Wl,-soname,gmp_cpp.so -o gmp_cpp.so gmp.o -lc -ldl -lgmp


LD_LIBRARY_PATH=/usr/lib/

ldconfig

./clever  gmp_cpp.clv

