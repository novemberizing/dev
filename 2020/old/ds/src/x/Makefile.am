AM_CFLAGS = -I$(top_srcdir)/src

noinst_LIBRARIES               = libnovemberizing.a

noinst_PROGRAMS                = novemberizing-check novemberizing-event

libnovemberizing_a_SOURCES     = val.c          \
                                 func.c         \
                                 sync.c         \
                                 thread.c       \
                                 list.c         \
                                 map.c

novemberizing_check_SOURCES    = check.c
novemberizing_check_LDADD      = libnovemberizing.a -lpthread

novemberizing_event_SOURCES    = event.c
novemberizing_event_LDADD      = libnovemberizing.a -lpthread
