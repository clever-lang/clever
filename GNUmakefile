#
# Clever programming language
# Copyright (c) 2011-2012 Clever Team
#
# Makefile - GNU Make recipes
#

##############################################################################
# Programs
SHELL  = /bin/sh
ECHO   = echo
MKDIR  = mkdir
CXX    = g++
SED    = sed
BISON  = bison
RE2C   = re2c
RM     = rm

#############################################################################
# Files and directories
MODDIR      := modules
OBJDIR      := build
TESTDIR     := tests
OBJFILES    :=
DEP_FILES   :=
ENSURE_DIRS :=

##############################################################################
# Environment
UNAME=$(shell uname)
IS_WIN32=$(if $(or $(findstring MINGW,$(UNAME)),$(findstring CYGWIN,$(UNAME))),yes,)
BINEXT=$(if $(findstring yes,$(IS_WIN32)),.exe,)


#############################################################################
# Helper functions
# has-goal goal
has-goal = $(strip $(if \
	$(or $(findstring all,$(MAKECMDGOALS)),$(findstring $1,$(MAKECMDGOALS))),yes,))
# is-empty string
is-empty = $(if $(strip $1),,yes)

include config.def.mk
-include config.mk

#############################################################################
# Clever variables
#ifeq ($(or $(call is-empty,$(MAKECMDGOALS)),$(call has-goal,clever),$(call has-goal,default)),yes)

clever_BIN  := clever$(BINEXT)
clever_SRC  := $(patsubst %.re,%.cc,$(patsubst %.y,%.cc,$(filter %.cc %.y %.re,\
	$(wildcard compiler/* vm/* interpreter/* types/*))))
clever_OBJ  := $(sort $(addprefix $(OBJDIR)/,$(patsubst %.cc,%.o,$(clever_SRC))))

clever_CXXFLAGS := -I. -DCLEVER_VERSION="\"$(VERSION)\"" \
	 -Wall -ansi -fno-rtti -fno-exceptions
clever_LDFLAGS  :=

#   add the module stuff
clv_mod    := $(addprefix $(MODDIR)/,$(subst .,/,$(MODULES)))
clv_modsrc := $(foreach mod,$(clv_mod),$(wildcard $(mod)/*.cc))
clv_modobj := $(addprefix $(OBJDIR)/,$(clv_modsrc:.cc=.o))
clv_mod    := $(addprefix mod_,$(subst .,_,$(MODULES)))
clv_modcxx := $(foreach mod,$(clv_mod),$($(mod)_CXXFLAGS))
clv_modld  := $(foreach mod,$(clv_mod),$($(mod)_LDFLAGS))

clever_SRC      += $(clv_modsrc)
clever_OBJ      += $(clv_modobj)
clever_CXXFLAGS += $(clv_modcxx)
clever_LDFLAGS  += $(clv_modld)

ifeq ($(IS_WIN32),yes)
clever_SRC += win32/win32.cc
clever_OBJ += $(OBJDIR)/win32/win32.o
clever_CXXFLAGS += -DCLEVER_WIN32
endif

OBJFILES    += $(clever_OBJ)
ENSURE_DIRS += $(sort $(dir $(clever_OBJ)))

#endif

#############################################################################
# Testrunner variables
#ifeq ($(call has-goal,test),true)
testrunner_BIN := extra/testrunner$(BINEXT)
testrunner_SRC := extra/testrunner.cc
testrunner_OBJ := $(addprefix $(OBJDIR)/,$(testrunner_SRC:.cc=.o))

ifeq ($(IS_WIN32),yes)
testrunner_CXXFLAGS := 
testrunner_LDFLAGS  := -lpcrecpp
else
testrunner_CXXFLAGS := $(shell pkg-config --cflags libpcrecpp)
testrunner_LDFLAGS  := $(shell pkg-config --libs libpcrecpp)
endif

OBJFILES    += $(testrunner_OBJ)
ENSURE_DIRS += $(sort $(dir $(testrunner_OBJ)))

#endif

##############################################################################
# More helpers
OBJFILES := $(sort $(OBJFILES))

COMPILE.cc = $(CXX) $(CXXFLAGS) -c
LINK.cc    = $(CXX) $(CXXFLAGS) $(LDFLAGS)
DEPEND.cc  = $(CXX) $(CXXFLAGS) -MM -MG

# cxx-command input output
cxx-command    = $(COMPILE.cc) -o $2 $1
# ld command input output
ld-command     = $(LINK.cc) -o $2 $1
# depend-command input output
depend-command = $(DEPEND.cc) $1 | $(SED) -e 's,^\([^:]*\):,$(patsubst %.d,%.o,$2) $2:,' > $2
# echo-command tool input
echo-command   = -$(ECHO) "  $1  $2"
# bison-command input output
bison-command  = $(BISON) -d -o$2 $1
# re2c-command input output
re2c-command   = $(RE2C) --case-insensitive -b -c -o$2 $1

ifeq ($(VERBOSE),yes)
echo-command =
else
.SILENT:
endif

ifeq ($(BUILD),devel)
override CXXFLAGS += -Wextra -ggdb3 -pg -D_DEBUG -DCLEVER_DEBUG
else ifeq ($(BUILD),debug)
override CXXFLAGS += -ggdb3 -D_DEBUG -DCLEVER_DEBUG
else
override CXXFLAGS +=-O2 -DNDEBUG
endif

.SUFFIXES:
.PHONY: all clean default test

default: $(clever_BIN)
all: $(clever_BIN) $(testrunner_BIN)
clean:
	-$(RM) -r -f $(OBJDIR) $(clever_BIN) $(testrunner_BIN)

#############################################################################
# Disable some implicit rules
%: RCS/%,v
%: RCS/%
%: SCCS/s.%
%: %,v
%: s.%

#############################################################################
# Generic recipes recipes

$(OBJDIR)/ensure-dirs:
	$(call echo-command,"MKDIR",$(sort $(ENSURE_DIRS)))
	$(MKDIR) -p $(sort $(ENSURE_DIRS))
	touch $@

$(OBJDIR)/%.o: %.cc $(OBJDIR)/ensure-dirs
	$(call echo-command,"CXX",$@)
	$(call cxx-command,$<,$@)

$(OBJDIR)/%.cc: %.y $(OBJDIR)/ensure-dirs
	$(call echo-command,"BISON",$@)
	$(call bison-command,$<,$@)

$(OBJDIR)/%.cc: %.re $(OBJDIR)/ensure-dirs
	$(call echo-command,"RE2C",$@)
	$(call re2c-command,$<,$@)

-include $(OBJFILES:.o=.d)

$(OBJDIR)/%.d: %.cc $(OBJDIR)/ensure-dirs
	$(call echo-command,"DEP",$@)
	$(call depend-command,$<,$@)

#############################################################################
# Clever recipes

$(clever_BIN): CXXFLAGS+=$(clever_CXXFLAGS)
$(clever_BIN): LDFLAGS+=$(clever_LDFLAGS)
$(clever_BIN): $(clever_OBJ) $(OBJDIR)/ensure-dirs
	$(call echo-command,"LD",$@)
	$(call ld-command,$(clever_OBJ),$@)

$(OBJDIR)/interpreter/scanner.o: $(OBJDIR)/interpreter/scanner.cc
	$(call echo-command,"CXX",$@)
	$(call cxx-command,$<,$@)

$(OBJDIR)/interpreter/parser.o: $(OBJDIR)/interpreter/parser.cc
	$(call echo-command,"CXX",$@)
	$(call cxx-command,$<,$@)

$(OBJDIR)/interpreter/parser.cc: interpreter/parser.y $(OBJDIR)/ensure-dirs
	$(call echo-command,"BISON",$@)
	$(call bison-command,$<,$@)
	$(SED) -ie '135s/|| \([^)]*\)/|| (\1)/' build/interpreter/position.hh

$(OBJDIR)/interpreter/scanner.d: $(OBJDIR)/interpreter/scanner.cc
$(OBJDIR)/interpreter/parser.d: $(OBJDIR)/interpreter/parser.cc
$(OBJDIR)/interpreter/location.hh: $(OBJDIR)/interpreter/parser.cc
$(OBJDIR)/interpreter/parser.hh: $(OBJDIR)/interpreter/parser.cc

#############################################################################
# Test runner recipes

$(testrunner_BIN): CXXFLAGS+=$(testrunner_CXXFLAGS)
$(testrunner_BIN): LDFLAGS+=$(testrunner_LDFLAGS)
$(testrunner_BIN): $(testrunner_OBJ) $(OBJDIR)/ensure-dirs
	echo $(testrunner_OBJ)
	$(call echo-command,"LD",$@)
	$(call ld-command,$(testrunner_OBJ),$@)

##############################################################################
# Tests
test: $(clever_BIN) $(testrunner_BIN)

run-mem-tests: test
	$(testrunner_BIN) -m $(TESTDIR)

run-tests: test
	$(testrunner_BIN) -q $(TESTDIR)

