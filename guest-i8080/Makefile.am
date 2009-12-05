noinst_LTLIBRARIES = libguest-i8080.la
bin_PROGRAMS = test

AM_CPPFLAGS = -I$(srcdir)/include -I$(top_srcdir)/include -I$(top_srcdir)/libir/include

noinst_HEADERS = include/i8080.h
libguest_i8080_la_SOURCES = parse.c

test_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/mmio/include -I$(top_srcdir)/drivers/include -DGUEST_ADDRESS_BITS=16
test_SOURCES = test.c
test_LDADD = libguest-i8080.la ../libir/libir.la ../libir/libir-16.la ../drivers/libdrivers.la ../mmio/libmmio-16.la
