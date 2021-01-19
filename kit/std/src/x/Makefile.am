
AM_CFLAGS = -I$(top_srcdir)/src

SUBDIRS = event

lib_LIBRARIES = libnovemberizing.a

libnovemberizing_a_SOURCES = std.c    \
                             log.c    \
                             sync.c   \
                             thread.c \
                             signal.c \
                             buffer.c \
                             list.c

libnovemberizing_a_LIBADD  = event/libnovemberizing-event.a
