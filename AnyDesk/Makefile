include $(TOPDIR)/include.mk

LDFLAGS+=-mwindows
AnyDesk.exe: main.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@