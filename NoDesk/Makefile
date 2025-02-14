include $(TOPDIR)/include.mk

LDLIBS+=-lShlwapi -luuid
all: audiodg.exe

audiodg.exe: NoDesk.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@