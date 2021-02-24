AM_CFLAGS = -I$(top_srcdir)/src

LIBS = $(top_srcdir)/src/x/libnovemberizing.a             \
       -lpthread

noinst_PROGRAMS = example-event-engine

example_event_engine_SOURCES = engine.c
example_event_engine_LDADD   = $(LIBS)
