# Warnings are expected.

# Environment
UNAME:=$(shell uname)
PREFIX?=/usr/local
FIND?=find

ifneq (,$(findstring MINGW,$(UNAME)))
IS_MINGW=1
endif

ifneq (,$(findstring CYGWIN,$(UNAME)))
IS_MINGW=1
endif

# Build options
CXXFLAGS?=-pipe

ifeq ($(DEBUG),y)
CXXFLAGS+=-ggdb3 -D_DEBUG -DCLEVER_DEBUG
else
CXXFLAGS+=-O2 -g -DNDEBUG
endif

# Programs
CXX?=g++
LD=$(CXX)
BISON?=bison
RE2C?=re2c

# Flags
CXXFLAGS+=-Wall -ansi -I. -fno-rtti -fno-exceptions
LFLAGS=$(CXXFLAGS)
BUILDDIR=build/
EXT=

# shortcuts
COMPILE=$(CXX) $(CXXFLAGS) -c
LINK=$(LD) $(LFLAGS)

VPATH=build compiler vm types interpreter extra test\
      modules/std modules/std/math modules/std/io modules/std/file

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o \
	$(BUILDDIR)cstring.o $(BUILDDIR)double.o $(BUILDDIR)std_pkg.o \
	$(BUILDDIR)int.o $(BUILDDIR)io.o $(BUILDDIR)math.o \
	$(BUILDDIR)file.o $(BUILDDIR)filestream.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)compiler.o \
	$(BUILDDIR)typeutils.o $(BUILDDIR)vm.o $(BUILDDIR)cgvisitor.o $(BUILDDIR)opcode.o \
	$(BUILDDIR)str.o $(BUILDDIR)main.o $(BUILDDIR)clever.o $(BUILDDIR)typechecker.o \
	$(BUILDDIR)symboltable.o

# Windows related stuff
ifdef IS_MINGW
EXT=.exe
OBJECTS+=$(BUILDDIR)win32.o
CXXFLAGS+=-Iwin32/
VPATH+=win32
endif

ifneq ($(VERBOSE),y)
.SILENT:
endif

.PHONY: clean

clever$(EXT): $(BUILDDIR)scanner.cc $(OBJECTS)
	@echo "  LD    $@"
	$(LINK) -o $@ $(OBJECTS)

all: clever$(EXT) test

$(BUILDDIR)ensure-build-dir:
	@echo "Making sure $(BUILDDIR) exists..."
	mkdir -p $(BUILDDIR)
	touch $(BUILDDIR)ensure-build-dir

$(BUILDDIR)%.o: %.cc %.d
	@echo "  CXX   $<"
	$(COMPILE) -o$@ $<

$(BUILDDIR)%.cc: %.y $(BUILDDIR)ensure-build-dir
	@echo "  BISON $<"
	$(BISON) -d -o$@ $<

$(BUILDDIR)%.cc: %.re $(BUILDDIR)ensure-build-dir
	@echo "  RE2C  $< "
	$(RE2C) --case-insensitive -b -c -o $@ $<

$(BUILDDIR)location.hh: $(BUILDDIR)parser.cc
$(BUILDDIR)parser.hh: $(BUILDDIR)parser.cc

test: clever extra/testrunner.cc extra/testrunner.h
	$(CXX) $(CXXFLAGS) -lpcrecpp -o extra/testrunner extra/testrunner.cc

run-mem-tests: test
	extra/testrunner -m tests/

run-tests: test
	extra/testrunner tests/

clean-all: clean clean-test clean-tests

clean:
	@echo "  CLEAN"
	-rm -f clever* $(BUILDDIR)*.o $(BUILDDIR)*.hh $(BUILDDIR)*.cc $(BUILDDIR)*.d
	-rm -rf $(BUILDDIR)

clean-tests:
	rm $(TESTDIR)*.mem $(TESTDIR)*.log

clean-test:
	rm -rf $(EXTRADIR)testrunner $(EXTRADIR)testrunner.exe

# No dependency tracking needed when cleaning
ifeq (,$(findstring clean,$(MAKECMDGOALS)))

$(BUILDDIR)%.d: %.cc $(BUILDDIR)ensure-build-dir
	$(CXX) -MM -MG $(CXXFLAGS) $< > $@.tmp
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@
	rm -f $@.tmp

-include $(subst .o,.d,$(OBJECTS))
endif

