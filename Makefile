#
# Clever programming language
# Copyright (c) 2011-2012 Clever Team
#
# Makefile - GNU Make recipes
#

#
# Clever stuff
#
BUILDDIR=build/
MODULEDIR=modules/

#
# Programs
#
SHELL=/bin/sh
SED=sed
ECHO=echo

#
# Environment
#
UNAME=$(shell uname)

# OS checks
ifneq ($(findstring MINGW,$(UNAME)),)
IS_WIN32=yes
else ifneq ($(findstring CYGWIN,$(UNAME)),)
IS_WIN32=yes
endif

#
# Build stuff
#
cxxflags=
ldflags=

include config.def.mk
-include config.mk

ifeq ($(BUILD),devel)
cxxflags+=-Wextra -ggdb3 -pg -D_DEBUG -DCLEVER_DEBUG
else ifeq ($(BUILD),debug)
cxxflags+=-ggdb3 -D_DEBUG -DCLEVER_DEBUG
else
cxxflags+=-O2 -g -DNDEBUG
endif

cxxflags:=$(cxxflags) $(CXXFLAGS) \
	  -DCLEVER_VERSION="\"$(VERSION)\"" \
	  -Wall -ansi -I. -fno-rtti -fno-exceptions

ldflags:=$(LDFLAGS)

BINEXT=

VPATH=build compiler vm types interpreter extra test

OBJECTS=$(BUILDDIR)parser.o $(BUILDDIR)scanner.o $(BUILDDIR)driver.o \
	$(BUILDDIR)cstring.o $(BUILDDIR)double.o \
	$(BUILDDIR)int.o $(BUILDDIR)pkgmanager.o $(BUILDDIR)compiler.o \
	$(BUILDDIR)vm.o $(BUILDDIR)cgvisitor.o $(BUILDDIR)opcode.o \
	$(BUILDDIR)str.o $(BUILDDIR)main.o $(BUILDDIR)clever.o $(BUILDDIR)typechecker.o \
	$(BUILDDIR)symboltable.o $(BUILDDIR)bool.o $(BUILDDIR)array.o

# Windows related stuff
ifdef IS_WIN32
BINEXT=.exe
OBJECTS+=$(BUILDDIR)win32.o
cxxflags+=-Iwin32/ -DCLEVER_WIN32
VPATH+=win32
endif

modnames:=
moddirs:=
modobj:=
modsrc:=
modcxxflags:=
modldflags:=

define gen_mod_vars =
override name__=$$(addprefix mod_,$$(subst .,_,$(1)))
$$(name__)_name:=$$(name__)
$$(name__)_dir:=$$(addprefix $(MODULEDIR),$$(subst .,/,$(1)))
$$(name__)_src:=$$(wildcard $$($$(name__)_dir)/*.cc)
$$(name__)_obj:=$$(addprefix $(BUILDDIR), $$($$(name__)_src:.cc=.o))
$$(name__)_objdir:=$$(addprefix $(BUILDDIR),$$($$(name__)_dir))

modnames:=$(modnames) $$($$(name__)_name)
moddirs:=$(moddirs) $$($$(name__)_dir)
modobj:=$(modobj) $$($$(name__)_obj)
modsrc:=$(modsrc) $$($$(name__)_src)
modcxxflags:=$(modcxxflags) $$($$(name__)_cxxflags)
modldflags:=$(modldflags) $$($$(name__)_ldflags)
endef

define gen_mod_recipes =
$(1): $$($(1)_obj) $(BUILDDIR)ensure-build-dir
$$($(1)_objdir)/%.o: $$($(1)_dir)/%.cc
	@$(ECHO) "  CXX  $$<"
	$$(COMPILE) $$($(1)_cxxflags) -o$$@ $$<
endef

$(foreach mod,$(MODULES),$(eval $(call gen_mod_vars,$(mod))))

#OBJECTS+=$(modobj)
#VPATH+=$(moddirs)

ifneq ($(VERBOSE),yes)
.SILENT:
endif

tmp_libdirs:=$(shell pkg-config --variable=libdir libpcrecpp)
tmp_libdirs:=$(foreach dir,$(tmp_libdirs),-L$(dir))
tmp_incdirs:=$(shell pkg-config --variable=includedir libpcrecpp)
tmp_incdirs:=$(foreach dir,$(tmp_incdirs),-I$(dir))
TESTRUNNER_FLAGS=$(tmp_libdirs) $(tmp_incdirs) $(shell pkg-config --cflags --libs libpcrecpp)

override CXXFLAGS = $(cxxflags)
override LDFLAGS = $(ldflags)

COMPILE=$(CXX) $(CXXFLAGS) -c
LINK=$(LD) $(CXXFLAGS) $(LDFLAGS) $(modcxxflags) $(modldflags)

.PHONY: clean all modules

clever$(BINEXT): $(BUILDDIR)scanner.cc $(OBJECTS) modules
	@$(ECHO) "  LD  $@"
	$(LINK) -o $@ $(OBJECTS) $(modobj)

all: clever$(BINEXT) test

modules: $(modnames)

$(foreach mod,$(modnames),$(eval $(call gen_mod_recipes,$(mod))))

$(BUILDDIR)ensure-build-dir:
	@echo "Making sure $(BUILDDIR) exists..."
	mkdir -p $(BUILDDIR) $(dir $(modobj))
	touch $(BUILDDIR)ensure-build-dir 

$(BUILDDIR)%.o: %.cc %.d
	@$(ECHO) "  CXX  $<"
	$(COMPILE) -o$@ $<

$(BUILDDIR)%.cc: %.y $(BUILDDIR)ensure-build-dir
	@$(ECHO) "  BISON  $<"
	$(BISON) -d -o$@ $<
	$(SED) -ie '135s/|| \([^)]*\)/|| (\1)/' build/position.hh

$(BUILDDIR)%.cc: %.re $(BUILDDIR)ensure-build-dir
	@$(ECHO) "  RE2C  $< "
	$(RE2C) --case-insensitive -b -c -o $@ $<

$(BUILDDIR)location.hh: $(BUILDDIR)parser.cc
$(BUILDDIR)parser.hh: $(BUILDDIR)parser.cc

test: clever extra/testrunner.cc extra/testrunner.h
	$(CXX) $(CXXFLAGS) $(TESTRUNNER_FLAGS) -o extra/testrunner extra/testrunner.cc

run-mem-tests: test
	extra/testrunner -m tests/

run-tests: test
	extra/testrunner -q tests/

clean-all: clean clean-test clean-tests

clean:
	@$(ECHO) "  CLEAN"
	-rm -f clever* $(BUILDDIR)*.o $(BUILDDIR)*.hh $(BUILDDIR)*.cc $(BUILDDIR)*.d
	-rm -rf $(BUILDDIR)

clean-tests:
	rm $(TESTDIR)*.mem $(TESTDIR)*.log

clean-test:
	rm -rf extra/testrunner extra/testrunner.exe

# No dependency tracking needed when cleaning
ifeq (,$(findstring clean,$(MAKECMDGOALS)))

$(BUILDDIR)%.d: %.cc $(BUILDDIR)ensure-build-dir
	$(CXX) -MM -MG $(CXXFLAGS) $< > $@.tmp
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@
	rm -f $@.tmp

-include $(subst .o,.d,$(OBJECTS))
endif

