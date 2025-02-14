
TOPDIR=$(CURDIR)

include include.mk
export TOPDIR

all: minhook-build libNoDeskCommon.a crt.dll audiodg.exe AnyDesk.exe

AnyDesk.exe:
	$(MAKE) -C AnyDesk

minhook-build:
	$(MAKE) -C minhook -f $(TOPDIR)/Makefile-MinHook

libNoDeskCommon.a:
	$(MAKE) -C NoDeskCommon

audiodg.exe:
	$(MAKE) -C NoDesk

crt.dll:
	$(MAKE) -C NoDeskRT

clean:
	-$(MAKE) -C minhook -f $(TOPDIR)/Makefile-MinHook clean
	-$(MAKE) -C NoDeskCommon clean
	-$(MAKE) -C NoDeskRT clean
	-$(MAKE) -C NoDesk clean
	echo "Cleared"