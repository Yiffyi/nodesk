include $(TOPDIR)/include.mk

INCLUDE+=-I$(TOPDIR)/minhook/include
LDLIBS+=-lMinHook -lShlwapi
LDFLAGS+=-L$(TOPDIR)/minhook 
all: crt.dll

crt.dll: dllmain.o DetourFunctions.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -shared -o $@