MAINTAINERCLEANFILES = Makefile.in

PACKAGE_NAME = @PACKAGE_NAME@

AM_CPPFLAGS = \
-I$(top_srcdir)/src/lib \
-I$(top_builddir)/src/lib \
-DPACKAGE_LIB_DIR=\"$(libdir)\" \
-DPACKAGE_DATA_DIR=\"$(datadir)/$(PACKAGE)\" \
@EFL_CFLAGS@ \
-DEFL_ENGINEER_BUILD

lib_LTLIBRARIES = libengineer.la

includes_HEADERS = Engineer.h
includesdir = $(includedir)/engineer-@VMAJ@

libengineer_la_SOURCES = engineer.c engineer_scene.c
libengineer_la_LIBADD = @EFL_LIBS@ -lm -ldb
libengineer_la_LDFLAGS = -no-undefined @EFL_LTLIBRARY_FLAGS@
