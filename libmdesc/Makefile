all: dtc

LDLIBS = -ly
YFLAGS = -d
CFLAGS = -Wall -Werror
CC = gcc-4.4

dtc: dtc.o dtc-parser.o

dtc.o: dtc.l y.tab.h

y.tab.h: dtc-parser.o

clean:
	-rm -f *.o *.tab.c *.tab.h dtc
