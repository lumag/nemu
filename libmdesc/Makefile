all: dtc

LDLIBS = -ly
YFLAGS = -d
CPPFLAGS = -Wall
CC = gcc-4.4

dtc: dtc.o dtc-parser.o

dtc.o: dtc.l dtc-parser.h

dtc-parser.h: dtc-parser.o

clean:
	-rm -f *.o *.tab.c *.tab.h dtc
