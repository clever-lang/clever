# $Id$
#

# Compiler
CXX?=g++
CPPFLAGS=-c -O2 -ggdb -ansi -Iinclude/ -Ibuild/ -Imodules/ -Iwin32/ -I. -fno-rtti -pedantic
CPPFLAGS2=-c -O2 -ggdb -ansi -Iinclude/ -Ibuild/ -I. -fno-rtti -pedantic
CPPFLAGS3=-ggdb
# Linker
LD=g++
LFLAGS=
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

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o $(BUILDDIR)cstring.o $(BUILDDIR)double.o $(BUILDDIR)std_pkg.o $(BUILDDIR)int.o $(BUILDDIR)io.o $(BUILDDIR)math.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)compiler.o $(BUILDDIR)vm.o $(BUILDDIR)opcode.o $(BUILDDIR)main.o $(BUILDDIR)win32.o

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o clever $(BUILDDIR)*.o

all: clever test

$(BUILDDIR)driver.o: $(SRCDIR)driver.cc $(BUILDDIR)parser.o $(BUILDDIR)compiler.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)driver.o $(SRCDIR)driver.cc

$(BUILDDIR)main.o: $(SRCDIR)main.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)main.o $(SRCDIR)main.cc

$(BUILDDIR)parser.cc: $(SRCDIR)parser.y
	$(BISON) -d -o$(BUILDDIR)parser.cc $(SRCDIR)parser.y

$(BUILDDIR)parser.o: $(BUILDDIR)parser.cc
	$(CXX) $(CPPFLAGS2) -o $(BUILDDIR)parser.o $(BUILDDIR)parser.cc

$(BUILDDIR)scanner.cc: $(SRCDIR)scanner.re $(BUILDDIR)parser.o
	$(RE2C) --case-insensitive -b -c -o $(BUILDDIR)scanner.cc $(SRCDIR)scanner.re

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cc $(BUILDDIR)cstring.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cc

$(BUILDDIR)cstring.o: $(SRCDIR)cstring.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)cstring.o $(SRCDIR)cstring.cc

$(BUILDDIR)compiler.o: $(SRCDIR)compiler.cc $(BUILDDIR)int.o $(BUILDDIR)double.o $(BUILDDIR)pkgmanager.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)compiler.o $(SRCDIR)compiler.cc

$(BUILDDIR)vm.o: $(SRCDIR)vm.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)vm.o $(SRCDIR)vm.cc

$(BUILDDIR)opcode.o: $(SRCDIR)opcode.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)opcode.o $(SRCDIR)opcode.cc

$(BUILDDIR)double.o: $(SRCDIR)double.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)double.o $(SRCDIR)double.cc

$(BUILDDIR)int.o: $(SRCDIR)int.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)int.o $(SRCDIR)int.cc

$(BUILDDIR)pkgmanager.o: $(SRCDIR)pkgmanager.cc $(BUILDDIR)std_pkg.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)pkgmanager.o $(SRCDIR)pkgmanager.cc

# Standard package
$(BUILDDIR)std_pkg.o: $(MODDIR)std/io.cc $(MODDIR)std/math.cc $(MODDIR)std/package.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)std_pkg.o $(MODDIR)std/package.cc

$(BUILDDIR)io.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/io.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)io.o $(MODDIR)std/io.cc

$(BUILDDIR)math.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/math.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)math.o $(MODDIR)std/math.cc

$(BUILDDIR)win32.o: $(WINDIR)win32.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)win32.o $(WINDIR)win32.cc

run-mem-tests:
	$(EXTRADIR)testrunner -m tests/

run-tests:
	$(EXTRADIR)testrunner tests/

test: $(EXTRADIR)testrunner.cpp
	$(CXX) $(CPPFLAGS3) -o $(EXTRADIR)testrunner $(EXTRADIR)testrunner.cpp -lpcrecpp

clean-all: clean clean-test

clean:
	rm -rf clever clever.exe
	rm -f $(BUILDDIR)*

clean-test:
	rm -rf $(EXTRADIR)testrunner $(EXTRADIR)testrunner.exe
