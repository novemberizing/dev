
AM_CFLAGS = -I$(top_srcdir)/src

noinst_PROGRAMS = novemberizing-x-example-sync          \
                  novemberizing-x-example-std           \
                  novemberizing-x-example-thread        \
                  novemberizing-x-example-threadlocal   \
                  novemberizing-x-example-buffer        \
                  novemberizing-x-example-list

novemberizing_x_example_sync_SOURCES        = sync.c
novemberizing_x_example_sync_LDADD          = $(top_srcdir)/src/x/libnovemberizing.a -lpthread

novemberizing_x_example_std_SOURCES         = std.c
novemberizing_x_example_std_LDADD           = $(top_srcdir)/src/x/libnovemberizing.a -lpthread

novemberizing_x_example_thread_SOURCES      = thread.c
novemberizing_x_example_thread_LDADD        = $(top_srcdir)/src/x/libnovemberizing.a -lpthread

novemberizing_x_example_threadlocal_SOURCES = threadlocal.c
novemberizing_x_example_threadlocal_LDADD   = $(top_srcdir)/src/x/libnovemberizing.a -lpthread

novemberizing_x_example_buffer_SOURCES      = buffer.c
novemberizing_x_example_buffer_LDADD        = $(top_srcdir)/src/x/libnovemberizing.a -lpthread

novemberizing_x_example_list_SOURCES        = list.c
novemberizing_x_example_list_LDADD          = $(top_srcdir)/src/x/libnovemberizing.a -lpthread