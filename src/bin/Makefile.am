MAINTAINERCLEANFILES = Makefile.in

PACKAGE_NAME = @PACKAGE_NAME@
bin_PROGRAMS = engineer engineer_math_test

EDIPREFIX=`pkg-config --variable=prefix efl`

AM_CPPFLAGS = -DPACKAGE_DATA_DIR=\"$(datadir)/$(PACKAGE)\" \
-I$(top_builddir)/src/bin/ \
-I$(top_srcdir)/src/bin/ \
-I$(top_builddir)/src/lib/ \
-I$(top_srcdir)/src/lib/ \
-I$(EDIPREFIX)/include/edi-0/ \
@EFL_CFLAGS@

engineer_SOURCES = engineer_main.c engineer_tabber.c engineer_user.c engineer_project.c engineer_window.c
engineer_LDADD = -ledi @EFL_LIBS@ $(top_builddir)/src/lib/libengineer.la

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

EXTRA_DIST = engineer_main.h

engineer_math_test_SOURCES = engineer_math_test_main.c
engineer_math_test_LDADD = @EFL_LIBS@ $(top_builddir)/src/lib/libengineer.la

