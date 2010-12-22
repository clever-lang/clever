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

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o $(BUILDDIR)types.o $(BUILDDIR)ast.o $(BUILDDIR)compiler.o $(BUILDDIR)vm.o $(BUILDDIR)main.o

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o clever $(BUILDDIR)*.o

all: clever test

$(BUILDDIR)driver.o: $(SRCDIR)driver.cc $(BUILDDIR)parser.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)driver.o $(SRCDIR)driver.cc

$(BUILDDIR)types.o: $(SRCDIR)types.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)types.o $(SRCDIR)types.cc

$(BUILDDIR)main.o: $(SRCDIR)main.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)main.o $(SRCDIR)main.cc

$(BUILDDIR)parser.cc: $(SRCDIR)parser.y
	$(BISON) -d -o$(BUILDDIR)parser.cc $(SRCDIR)parser.y

$(BUILDDIR)parser.o: $(BUILDDIR)parser.cc
	$(CXX) $(CPPFLAGS3) -o $(BUILDDIR)parser.o $(BUILDDIR)parser.cc

$(BUILDDIR)scanner.cc: $(SRCDIR)scanner.re $(BUILDDIR)parser.o
	$(RE2C) --case-insensitive -b -c -o $(BUILDDIR)scanner.cc $(SRCDIR)scanner.re

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cc

$(BUILDDIR)ast.o: $(SRCDIR)ast.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)ast.o $(SRCDIR)ast.cc

$(BUILDDIR)compiler.o: $(SRCDIR)compiler.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)compiler.o $(SRCDIR)compiler.cc

$(BUILDDIR)vm.o: $(SRCDIR)vm.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)vm.o $(SRCDIR)vm.cc

clean:
	rm -f clever $(BUILDDIR)*
