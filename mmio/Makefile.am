noinst_LTLIBRARIES = libmmio-16.la
noinst_HEADERS = include/mmio.h include/mmio-defs.h include/mmio-drv.h

libmmio_16_la_CPPFLAGS = $(AM_CPPFLAGS) -DGUEST_ADDRESS_BITS=16
libmmio_16_la_SOURCES = mmio-pgd.c mmio-undef.c

AM_CPPFLAGS = -I$(srcdir)/include
