include $(TOPDIR)/include.mk

LDLIBS+=-lShlwapi -luuid
LDFLAGS+=-mwindows
all: audiodg.exe

audiodg.exe: NoDesk.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@

clean:
	-del /q audiodg.exe *.o