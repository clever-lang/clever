# $Id$
#

# Compiler
CXX?=g++
CXXFLAGS=-c -O2 -ggdb -ansi -Iinclude/ -Ibuild/ -Imodules/ -Iwin32/ -I. -fno-rtti -pedantic -fno-exceptions
CXXFLAGS2=-c -O2 -ggdb -ansi -Iinclude/ -Ibuild/ -I. -fno-rtti -pedantic -fno-exceptions
CXXFLAGS3=-ggdb -O2
# Linker
LD=g++
LFLAGS=-O2 -fno-rtti -fno-exceptions
# Bison, re2c
BISON=bison
RE2C=re2c
# Build dir
BUILDDIR=build/
# Core source dir
SRCDIR=src/
# Module dir
MODDIR=modules/
# Win32 port dir
WINDIR=win32/
# Testrunner dir
EXTRADIR=extra/

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o \
	$(BUILDDIR)cstring.o $(BUILDDIR)double.o $(BUILDDIR)std_pkg.o \
	$(BUILDDIR)int.o $(BUILDDIR)io.o $(BUILDDIR)math.o \
	$(BUILDDIR)pkgmanager.o $(BUILDDIR)compiler.o \
	$(BUILDDIR)vm.o $(BUILDDIR)astvisitor.o $(BUILDDIR)opcode.o \
	$(BUILDDIR)main.o $(BUILDDIR)win32.o

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS)

all: clever test

$(BUILDDIR)driver.o: $(SRCDIR)driver.cc $(BUILDDIR)parser.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)driver.o $(SRCDIR)driver.cc

$(BUILDDIR)main.o: $(SRCDIR)main.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)main.o $(SRCDIR)main.cc

$(BUILDDIR)parser.cc: $(SRCDIR)parser.y
	$(BISON) -d -o$(BUILDDIR)parser.cc $(SRCDIR)parser.y

$(BUILDDIR)parser.o: $(BUILDDIR)parser.cc
	$(CXX) $(CXXFLAGS2) -o $(BUILDDIR)parser.o $(BUILDDIR)parser.cc

$(BUILDDIR)scanner.cc: $(SRCDIR)scanner.re $(BUILDDIR)parser.o
	$(RE2C) --case-insensitive -b -c -o $(BUILDDIR)scanner.cc $(SRCDIR)scanner.re

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cc $(BUILDDIR)cstring.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cc

$(BUILDDIR)cstring.o: $(SRCDIR)cstring.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)cstring.o $(SRCDIR)cstring.cc

$(BUILDDIR)compiler.o: $(SRCDIR)compiler.cc $(BUILDDIR)driver.o $(BUILDDIR)int.o $(BUILDDIR)double.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)astvisitor.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)compiler.o $(SRCDIR)compiler.cc

$(BUILDDIR)astvisitor.o: $(SRCDIR)astvisitor.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)astvisitor.o $(SRCDIR)astvisitor.cc

$(BUILDDIR)vm.o: $(SRCDIR)vm.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)vm.o $(SRCDIR)vm.cc

$(BUILDDIR)opcode.o: $(SRCDIR)opcode.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)opcode.o $(SRCDIR)opcode.cc

$(BUILDDIR)double.o: $(SRCDIR)double.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)double.o $(SRCDIR)double.cc

$(BUILDDIR)int.o: $(SRCDIR)int.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)int.o $(SRCDIR)int.cc

$(BUILDDIR)pkgmanager.o: $(SRCDIR)pkgmanager.cc $(BUILDDIR)std_pkg.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)pkgmanager.o $(SRCDIR)pkgmanager.cc

# Standard package
$(BUILDDIR)std_pkg.o: $(MODDIR)std/io.cc $(MODDIR)std/math.cc $(MODDIR)std/std_pkg.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)std_pkg.o $(MODDIR)std/std_pkg.cc

$(BUILDDIR)io.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/io.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)io.o $(MODDIR)std/io.cc

$(BUILDDIR)math.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/math.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)math.o $(MODDIR)std/math.cc

$(BUILDDIR)win32.o: $(WINDIR)win32.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)win32.o $(WINDIR)win32.cc

run-mem-tests:
	$(EXTRADIR)testrunner -m tests/

run-tests:
	$(EXTRADIR)testrunner tests/

test: $(EXTRADIR)testrunner.cpp
	$(CXX) $(CXXFLAGS3) -o $(EXTRADIR)testrunner $(EXTRADIR)testrunner.cpp -lpcrecpp

clean-all: clean clean-test

clean:
	rm -rf clever clever.exe
	rm -f $(BUILDDIR)*

clean-test:
	rm -rf $(EXTRADIR)testrunner $(EXTRADIR)testrunner.exe
