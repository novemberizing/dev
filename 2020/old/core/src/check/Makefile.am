# NOVEMBERIZING'S CORE CHECK
AM_CFLAGS = -I$(top_srcdir)/src

SUBDIRS = x

noinst_PROGRAMS = novemberizing-check

novemberizing_check_SOURCES = check.c
novemberizing_check_LDADD = x/libnovemberizing-check.a ../x/libnovemberizing.a
