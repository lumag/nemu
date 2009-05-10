noinst_LTLIBRARIES = libir.la libir-16.la

AM_CPPFLAGS = -I$(srcdir)/include -I$(top_srcdir)/include -I$(top_srcdir)/mmio/include

noinst_HEADERS = include/ir.h
libir_la_SOURCES = ir.c dump_ir.c

libir_16_la_CPPFLAGS = $(AM_CPPFLAGS) -DGUEST_ADDRESS_BITS=16
libir_16_la_SOURCES = interp.c
