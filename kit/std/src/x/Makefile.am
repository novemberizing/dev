AM_CFLAGS = -I$(top_srcdir)/src
ACLOCAL_AMFLAGS = -I m4

lib_LIBRARIES = libnovemberizing.a

libnovemberizing_a_SOURCES = std.c              \
                             thread.c           \
                             thread/posix.c     \
                             sync.c             \
                             sync/posix/mutex.c \
                             stream.c           \
                             stream/buffer.c
