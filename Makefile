# Environment detection
UNAME := $(shell uname)

ifneq (,$(findstring MINGW,$(UNAME)))
IS_MINGW=1
endif

# Programs
CXX?=g++
LD=g++
BISON?=bison
RE2C?=re2c

# Flags

CXXFLAGS=-O2 -ggdb -Wall -ansi -I. -fno-rtti -pedantic -fno-exceptions
CXXFLAGS3=-ggdb -O2
# Linker
LFLAGS=-O2 -fno-rtti -fno-exceptions
# Bison, re2c
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
# Test dir
TESTDIR=test/

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o \
	$(BUILDDIR)cstring.o $(BUILDDIR)double.o $(BUILDDIR)std_pkg.o \
	$(BUILDDIR)int.o $(BUILDDIR)io.o $(BUILDDIR)math.o \
	$(BUILDDIR)file.o $(BUILDDIR)filestream.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)compiler.o \
	$(BUILDDIR)typeutils.o $(BUILDDIR)vm.o $(BUILDDIR)cgvisitor.o $(BUILDDIR)opcode.o \
	$(BUILDDIR)str.o $(BUILDDIR)main.o 

# Windows related stuff
ifdef IS_MINGW
OBJECTS+=$(BUILDDIR)win32.o
CXXFLAGS+=-Iwin32/
endif

clever: $(OBJECTS)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS)

all: clever test

$(BUILDDIR)driver.o: $(INTERPDIR)driver.cc $(BUILDDIR)parser.o
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)driver.o $(INTERPDIR)driver.cc

$(BUILDDIR)main.o: $(INTERPDIR)main.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)main.o $(INTERPDIR)main.cc

$(BUILDDIR)parser.cc: $(INTERPDIR)parser.y
	mkdir -p build
	$(BISON) -d -o$(BUILDDIR)parser.cc $(INTERPDIR)parser.y

$(BUILDDIR)parser.o: $(BUILDDIR)parser.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)parser.o $(BUILDDIR)parser.cc

$(BUILDDIR)scanner.cc: $(INTERPDIR)scanner.re $(BUILDDIR)parser.o
	$(RE2C) --case-insensitive -b -c -o $(BUILDDIR)scanner.cc $(INTERPDIR)scanner.re

$(BUILDDIR)scanner.o: $(BUILDDIR)scanner.cc $(BUILDDIR)cstring.o
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)scanner.o $(BUILDDIR)scanner.cc

$(BUILDDIR)cstring.o: $(COMPDIR)cstring.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)cstring.o $(COMPDIR)cstring.cc

$(BUILDDIR)compiler.o: $(COMPDIR)compiler.cc $(BUILDDIR)driver.o $(BUILDDIR)int.o $(BUILDDIR)double.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)cgvisitor.o
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)compiler.o $(COMPDIR)compiler.cc

$(BUILDDIR)cgvisitor.o: $(COMPDIR)cgvisitor.cc $(BUILDDIR)typeutils.o
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)cgvisitor.o $(COMPDIR)cgvisitor.cc

$(BUILDDIR)vm.o: $(VMDIR)vm.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)vm.o $(VMDIR)vm.cc

$(BUILDDIR)opcode.o: $(VMDIR)opcode.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)opcode.o $(VMDIR)opcode.cc

$(BUILDDIR)pkgmanager.o: $(COMPDIR)pkgmanager.cc $(BUILDDIR)std_pkg.o
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)pkgmanager.o $(COMPDIR)pkgmanager.cc

# Types
$(BUILDDIR)typeutils.o: $(TYPEDIR)typeutils.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)typeutils.o $(TYPEDIR)typeutils.cc

$(BUILDDIR)double.o: $(TYPEDIR)double.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)double.o $(TYPEDIR)double.cc

$(BUILDDIR)int.o: $(TYPEDIR)int.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)int.o $(TYPEDIR)int.cc

$(BUILDDIR)str.o: $(TYPEDIR)str.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)str.o $(TYPEDIR)str.cc

# Standard package
$(BUILDDIR)std_pkg.o: $(MODDIR)std/io/io.cc $(MODDIR)std/math/math.cc $(MODDIR)std/file/file.cc $(MODDIR)std/std_pkg.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)std_pkg.o $(MODDIR)std/std_pkg.cc

$(BUILDDIR)io.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/io/io.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)io.o $(MODDIR)std/io/io.cc

$(BUILDDIR)math.o: $(BUILDDIR)pkgmanager.o $(MODDIR)std/math/math.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)math.o $(MODDIR)std/math/math.cc

$(BUILDDIR)filestream.o: $(MODDIR)std/file/filestream.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)filestream.o $(MODDIR)std/file/filestream.cc

$(BUILDDIR)file.o: $(BUILDDIR)pkgmanager.o $(BUILDDIR)filestream.o $(MODDIR)std/file/file.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)file.o $(MODDIR)std/file/file.cc

$(BUILDDIR)win32.o: $(WINDIR)win32.cc
	$(CXX) $(CXXFLAGS) -c -o $(BUILDDIR)win32.o $(WINDIR)win32.cc

run-mem-tests:
	$(EXTRADIR)testrunner -m tests/

run-tests:
	$(EXTRADIR)testrunner tests/

test: $(EXTRADIR)testrunner.cc
	$(CXX) $(CXXFLAGS3) -o $(EXTRADIR)testrunner $(EXTRADIR)testrunner.cc -lpcrecpp

clean-all: clean clean-test clean-tests

clean:
	rm -f clever* $(BUILDDIR)*.o $(BUILDDIR)*.hh $(BUILDDIR)*.cc

clean-tests:
	rm $(TESTDIR)*.mem $(TESTDIR)*.log

clean-test:
	rm -rf $(EXTRADIR)testrunner $(EXTRADIR)testrunner.exe
