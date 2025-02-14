
TOPDIR=$(CURDIR)

include include.mk
export TOPDIR

all: minhook-build libNoDeskCommon.a crt.dll audiodg.exe

test.exe:
	$(MAKE) -C test

minhook-clean:
	$(MAKE) -C minhook -f build/MinGW/Makefile clean

minhook-build:
	$(MAKE) -C minhook -f build/MinGW/Makefile

libNoDeskCommon.a:
	$(MAKE) -C NoDeskCommon

audiodg.exe:
	$(MAKE) -C NoDesk

crt.dll:
	$(MAKE) -C NoDeskRT

clean: minhook-clean
	echo "Cleared"