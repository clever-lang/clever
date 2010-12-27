# $Id$
#
# Compiler
CXX?=g++
CPPFLAGS=-c -ggdb -ansi -Iinclude/ -Ibuild/ -Imodules/ -Iwin32/ -I. -fno-rtti
CPPFLAGS2=-ggdb -ansi
CPPFLAGS3=-c -ggdb -ansi -Iinclude/ -Ibuild/ -I. -fno-rtti
CPPFLAGS4=-ggdb
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
# Win32 port dir
WINDIR=win32/
# Testrunner dir
EXTRADIR=extra/

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o $(BUILDDIR)types.o $(BUILDDIR)cstring.o $(BUILDDIR)irbuilder.o $(BUILDDIR)ast.o $(BUILDDIR)compiler.o $(BUILDDIR)vm.o $(BUILDDIR)opcodes.o $(BUILDDIR)main.o $(BUILDDIR)win32.o

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

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cc $(BUILDDIR)cstring.o
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cc

$(BUILDDIR)cstring.o: $(SRCDIR)cstring.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)cstring.o $(SRCDIR)cstring.cc

$(BUILDDIR)ast.o: $(SRCDIR)ast.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)ast.o $(SRCDIR)ast.cc

$(BUILDDIR)irbuilder.o: $(SRCDIR)irbuilder.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)irbuilder.o $(SRCDIR)irbuilder.cc

$(BUILDDIR)compiler.o: $(SRCDIR)compiler.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)compiler.o $(SRCDIR)compiler.cc

$(BUILDDIR)vm.o: $(SRCDIR)vm.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)vm.o $(SRCDIR)vm.cc

$(BUILDDIR)opcodes.o: $(SRCDIR)opcodes.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)opcodes.o $(SRCDIR)opcodes.cc

$(BUILDDIR)win32.o: $(WINDIR)win32.cc
	$(CXX) $(CPPFLAGS) -o $(BUILDDIR)win32.o $(WINDIR)win32.cc

run-mem-tests:
	$(EXTRADIR)testrunner -m tests/

run-tests:
	$(EXTRADIR)testrunner tests/

test: $(EXTRADIR)testrunner.cpp
	$(CXX) $(CPPFLAGS4) -o $(EXTRADIR)testrunner $(EXTRADIR)testrunner.cpp -lpcrecpp

clean-all: clean clean-test

clean:
	rm -rf clever clever.exe
	rm -f $(BUILDDIR)*

clean-test:
	rm -rf $(EXTRADIR)testrunner $(EXTRADIR)testrunner.exe