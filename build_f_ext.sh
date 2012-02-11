g++ -fPIC -O3 -shared -c f_ext.cpp
g++ -shared -Wl,-soname,libfext3.so -o libfext3.so f_ext.o -lc -ldl


install libfext3.so /usr/local/lib
ldconfig


