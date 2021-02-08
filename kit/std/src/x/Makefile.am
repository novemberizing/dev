AM_CFLAGS = -I$(top_srcdir)/src
ACLOCAL_AMFLAGS = -I m4

lib_LIBRARIES = libnovemberizing.a

libnovemberizing_a_SOURCES = std.c                  \
                             log.c                  \
                             time.c                 \
                             thread.c               \
                             stream.c               \
                             io.c                   \
                             descriptor.c           \
                             descriptorio.c         \
                             descriptorio-epoll.c   \
                             socket.c               \
                             client.c               \
                             server.c               \
                             session.c

# libnovemberizing_a_LIBADD  = net/libnovemberizing-net.a event/libnovemberizing-event.a
