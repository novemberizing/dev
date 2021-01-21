
AM_CFLAGS = -I$(top_srcdir)/src
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = event net

lib_LIBRARIES = libnovemberizing.a

libnovemberizing_a_SOURCES = std.c    \
                             log.c    \
                             sync.c   \
                             thread.c \
                             signal.c \
                             buffer.c \
                             list.c

libnovemberizing_a_LIBADD  = net/libnovemberizing-net.a event/libnovemberizing-event.a
