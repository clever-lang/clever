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
MODULES=std std.math std.io std.file std.os std.reflection std.net

# module flags (example)
mod_std_math_CXXFLAGS =
mod_std_math_LDFLAGS  = -lm

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

