AM_CFLAGS = -I$(top_srcdir)/src

noinst_LIBRARIES               = libnovemberizing-ds.a
noinst_PROGRAMS                = novemberizing-ds-check

libnovemberizing_ds_a_SOURCES  = xtypes.c   \
                                 xlist.c    \
                                 xmap.c

novemberizing_ds_check_SOURCES = check.c
novemberizing_ds_check_LDADD   = libnovemberizing-ds.a

