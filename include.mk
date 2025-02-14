CC:=gcc
MAKE=mingw32-make

LDLIBS=-lNoDeskCommon
LDFLAGS:=-L$(TOPDIR)/NoDeskCommon -m32

INCLUDE=-I$(TOPDIR)/NoDeskCommon
CFLAGS=-Wall -m32 $(INCLUDE)
# CFLAGS:=-masm=intel -Wall -Werror -std=c11 $(INCS)
# LDFLAGS:=-Wl,-enable-stdcall-fixup -s -static
