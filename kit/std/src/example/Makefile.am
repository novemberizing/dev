

AM_CFLAGS = -I$(top_srcdir)/src



noinst_PROGRAMS = example

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

example_SOURCES        = main.c
example_LDADD          = $(LIBS)
