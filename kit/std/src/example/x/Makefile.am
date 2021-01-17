
AM_CFLAGS = -I$(top_srcdir)/src

noinst_PROGRAMS = novemberizing-x-example-sync  \
                  novemberizing-x-example-std

novemberizing_x_example_sync_SOURCES = sync.c
novemberizing_x_example_sync_LDADD   = $(top_srcdir)/src/x/libnovemberizing.a -lpthread

novemberizing_x_example_std_SOURCES  = std.c
novemberizing_x_example_std_LDADD    = $(top_srcdir)/src/x/libnovemberizing.a -lpthread
