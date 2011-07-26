# $Id$
#
UNAME := $(shell uname)

# Compiler
CXX?=g++
CXXFLAGS=-c -O2 -ggdb -Wall -ansi -Ibuild/ -Imodules/ -I. -fno-rtti -pedantic -fno-exceptions
CXXFLAGS2=-c -O2 -ggdb -ansi -Ibuild/ -I. -fno-rtti -pedantic -fno-exceptions
CXXFLAGS3=-ggdb -O2
# Linker
LD=g++
LFLAGS=-O2 -fno-rtti -fno-exceptions
# Bison, re2c
BISON=bison
RE2C=re2c
# Build dir
BUILDDIR=build/
# Compiler dir
COMPDIR=compiler/
# VM dir
VMDIR=vm/
# Type dir
TYPEDIR=types/
# Interpreter dir
INTERPDIR=interpreter/
# Module dir
MODDIR=modules/
# Win32 port dir
WINDIR=win32/
# Testrunner dir
EXTRADIR=extra/

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o \
	$(BUILDDIR)cstring.o $(BUILDDIR)double.o $(BUILDDIR)std_pkg.o \
	$(BUILDDIR)int.o $(BUILDDIR)io.o $(BUILDDIR)math.o \
	$(BUILDDIR)file.o $(BUILDDIR)filestream.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)compiler.o \
	$(BUILDDIR)vm.o $(BUILDDIR)cgvisitor.o $(BUILDDIR)opcode.o \
	$(BUILDDIR)string_type.o $(BUILDDIR)main.o $(BUILDDIR)win32.o

# Windows related stuff
ifneq (,$(findstring MINGW,$(UNAME)))
OBJECTS+=$(BUILDDIR)win32.o
CXXFLAGS+=-Iwin32/
endif

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS)

all: clever test

$(BUILDDIR)driver.o: $(INTERPDIR)driver.cc $(BUILDDIR)parser.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)driver.o $(INTERPDIR)driver.cc

$(BUILDDIR)main.o: $(INTERPDIR)main.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)main.o $(INTERPDIR)main.cc

$(BUILDDIR)parser.cc: $(INTERPDIR)parser.y
	$(BISON) -d -o$(BUILDDIR)parser.cc $(INTERPDIR)parser.y

$(BUILDDIR)parser.o: $(BUILDDIR)parser.cc
	$(CXX) $(CXXFLAGS2) -o $(BUILDDIR)parser.o $(BUILDDIR)parser.cc

$(BUILDDIR)scanner.cc: $(INTERPDIR)scanner.re $(BUILDDIR)parser.o
	$(RE2C) --case-insensitive -b -c -o $(BUILDDIR)scanner.cc $(INTERPDIR)scanner.re

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cc $(BUILDDIR)cstring.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cc

$(BUILDDIR)cstring.o: $(COMPDIR)cstring.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)cstring.o $(COMPDIR)cstring.cc

$(BUILDDIR)compiler.o: $(COMPDIR)compiler.cc $(BUILDDIR)driver.o $(BUILDDIR)int.o $(BUILDDIR)double.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)cgvisitor.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)compiler.o $(COMPDIR)compiler.cc

$(BUILDDIR)cgvisitor.o: $(COMPDIR)cgvisitor.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)cgvisitor.o $(COMPDIR)cgvisitor.cc

$(BUILDDIR)vm.o: $(VMDIR)vm.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)vm.o $(VMDIR)vm.cc

$(BUILDDIR)opcode.o: $(VMDIR)opcode.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)opcode.o $(VMDIR)opcode.cc

$(BUILDDIR)pkgmanager.o: $(COMPDIR)pkgmanager.cc $(BUILDDIR)std_pkg.o
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)pkgmanager.o $(COMPDIR)pkgmanager.cc

# Types
$(BUILDDIR)double.o: $(TYPEDIR)double.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)double.o $(TYPEDIR)double.cc

$(BUILDDIR)int.o: $(TYPEDIR)int.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)int.o $(TYPEDIR)int.cc

$(BUILDDIR)string_type.o: $(TYPEDIR)string_type.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)string_type.o $(TYPEDIR)string_type.cc

# Standard package
$(BUILDDIR)std_pkg.o: $(MODDIR)std/io/io.cc $(MODDIR)std/math/math.cc $(MODDIR)std/file/file.cc $(MODDIR)std/std_pkg.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)std_pkg.o $(MODDIR)std/std_pkg.cc

$(BUILDDIR)io.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/io/io.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)io.o $(MODDIR)std/io/io.cc

$(BUILDDIR)math.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/math/math.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)math.o $(MODDIR)std/math/math.cc

$(BUILDDIR)filestream.o: $(MODDIR)std/file/filestream.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)filestream.o $(MODDIR)std/file/filestream.cc

$(BUILDDIR)file.o: $(BUILDDIR)pkgmanager.o $(BUILDDIR)filestream.o $(MODDIR)std/file/file.cc
	$(CXX) $(CXXFLAGS) -o $(BUILDDIR)file.o $(MODDIR)std/file/file.cc

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
	rm -f clever* $(BUILDDIR)*.o $(BUILDDIR)*.hh $(BUILDDIR)*.cc

clean-test:
	rm -rf $(EXTRADIR)testrunner $(EXTRADIR)testrunner.exe
