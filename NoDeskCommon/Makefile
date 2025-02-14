include $(TOPDIR)/include.mk

OBJS=NoDesk/process.o NoDesk/strings.o NoDesk/paths.o

all: libNoDeskCommon.a

libNoDeskCommon.a: $(OBJS)
	$(AR) r $@ $^