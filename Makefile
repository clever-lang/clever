# Compiler
CXX?=g++
CPPFLAGS=-c -ggdb -ansi -Iinclude/ -Ibuild/ -Imodules/ -I.
CPPFLAGS2=-ggdb -ansi
CPPFLAGS3=-c -ggdb -ansi -Iinclude/ -Ibuild/ -I.
# Linker
LD=g++
LFLAGS=-ggdb -O2
# Bison, re2c
BISON=bison
RE2C=re2c
# Build dir
BUILDDIR=build/
# Core source dir
SRCDIR=core/
# Testrunner dir
EXTRADIR=extra/

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o $(BUILDDIR)types.o $(BUILDDIR)ast.o $(BUILDDIR)compiler.o $(BUILDDIR)main.o

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o clever $(BUILDDIR)*.o

all: clever test

$(BUILDDIR)driver.o: $(SRCDIR)driver.cpp $(BUILDDIR)parser.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)driver.o $(SRCDIR)driver.cpp

$(BUILDDIR)types.o: $(SRCDIR)types.cpp
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)types.o $(SRCDIR)types.cpp

$(BUILDDIR)main.o: $(SRCDIR)main.cpp
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)main.o $(SRCDIR)main.cpp

$(BUILDDIR)parser.cpp: $(SRCDIR)parser.y
	$(BISON) -d -o$(BUILDDIR)parser.cpp $(SRCDIR)parser.y
	
$(BUILDDIR)parser.o: $(BUILDDIR)parser.cpp
	$(CXX) $(CPPFLAGS3) -o $(BUILDDIR)parser.o $(BUILDDIR)parser.cpp
 
$(BUILDDIR)scanner.cpp: $(SRCDIR)scanner.re $(BUILDDIR)parser.o
	$(RE2C) --case-insensitive -b -c -o $(BUILDDIR)scanner.cpp $(SRCDIR)scanner.re

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cpp
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cpp
	
$(BUILDDIR)ast.o: $(SRCDIR)ast.cpp
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)ast.o $(SRCDIR)ast.cpp
	
$(BUILDDIR)compiler.o: $(SRCDIR)compiler.cpp
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)compiler.o $(SRCDIR)compiler.cpp

clean:
	rm -f clever $(BUILDDIR)*

clean-tests:
	rm -rf tests/*.log tests/*.mem
	
clean-all: clean clean-tests
