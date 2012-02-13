#
# Clever programming language
# Copyright (c) 2011-2012 Clever Team
#
# config.def.mk - Default build options
#

#
# Clever stuff
#
VERSION=devel
MODULES=std std.math std.io std.file std.os std.reflection std.net std.regex

ifeq ($(IS_WIN32),yes)
mod_std_regex_CXXFLAGS =
mod_std_regex_LDFLAGS  = -lpcrecpp
else
mod_std_regex_CXXFLAGS = $(shell pkg-config --cflags libpcrecpp)
mod_std_regex_LDFLAGS  = $(shell pkg-config --libs libpcrecpp)
endif

# Disable ffi on windows or when NO_FFI=yes is used
ifneq ($(or $(NO_FFI),$(IS_WIN32)),yes)
MODULES += std.ffi
mod_std_ffi_CXXFLAGS = -DHAVE_FFI $(shell pkg-config --cflags libffi)
mod_std_ffi_LDFLAGS  = $(shell pkg-config --libs libffi)
endif

#
# Environment
#
PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
MANDIR=$(PREFIX)/share/man

#
# Compiler and linker
#
CXX=g++
LD=$(CXX)
CXXFLAGS=-pipe
LDFLAGS=

#
# Parser and tokenizer generators
#
BISON=bison
RE2C=re2c

#
# Build
#

# Build mode (devel, debug or release)
BUILD=debug
# Show commands?
VERBOSE=no

