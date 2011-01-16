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

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o $(BUILDDIR)cstring.o $(BUILDDIR)double.o $(BUILDDIR)int.o $(BUILDDIR)irbuilder.o $(BUILDDIR)std.o $(BUILDDIR)compiler.o $(BUILDDIR)vm.o $(BUILDDIR)opcode.o $(BUILDDIR)main.o $(BUILDDIR)win32.o

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o clever $(BUILDDIR)*.o

all: clever test

$(BUILDDIR)driver.o: $(SRCDIR)driver.cc $(BUILDDIR)parser.o
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

$(BUILDDIR)irbuilder.o: $(SRCDIR)irbuilder.cc $(BUILDDIR)compiler.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)irbuilder.o $(SRCDIR)irbuilder.cc

$(BUILDDIR)compiler.o: $(SRCDIR)compiler.cc $(BUILDDIR)int.o $(BUILDDIR)double.o $(BUILDDIR)std.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)compiler.o $(SRCDIR)compiler.cc

$(BUILDDIR)vm.o: $(SRCDIR)vm.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)vm.o $(SRCDIR)vm.cc

$(BUILDDIR)opcode.o: $(SRCDIR)opcode.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)opcode.o $(SRCDIR)opcode.cc

$(BUILDDIR)double.o: $(SRCDIR)double.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)double.o $(SRCDIR)double.cc

$(BUILDDIR)int.o: $(SRCDIR)int.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)int.o $(SRCDIR)int.cc

$(BUILDDIR)std.o: $(MODDIR)std/std.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)std.o $(MODDIR)std/std.cc

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
