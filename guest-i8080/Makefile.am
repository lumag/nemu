noinst_LTLIBRARIES = libguest-i8080.la
bin_PROGRAMS = test

AM_CPPFLAGS = -I$(srcdir)/include -I$(top_srcdir)/include -I$(top_srcdir)/libir/include -I$(top_srcdir)/mmio/include

noinst_HEADERS = include/i8080.h include/guest.h
libguest_i8080_la_SOURCES = parse.c

test_CPPFLAGS = $(AM_CPPFLAGS) -DGUEST_ADDRESS_BITS=16
test_SOURCES = test.c i7seg.c
test_LDADD = libguest-i8080.la ../libir/libir.la ../libir/libir-16.la ../mmio/libmmio-16.la
