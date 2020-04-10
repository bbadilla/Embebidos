AM_CPPFLAGS = -I$(top_srcdir)/include
bin_PROGRAMS = proyecto1
proyecto1_SOURCES = main.c mqtt.c
proyecto1_LDADD = $(top_builddir)/lib/libgpio.la $(top_builddir)/lib/libutilities.la -lpaho-mqtt3a
