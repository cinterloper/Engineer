
if EFL_HAVE_TESTS

check_PROGRAMS = engineer_tests

engineer_tests_SOURCES = test_engineer.c
engineer_tests_CPPFLAGS = -I$(top_builddir)/src/lib/ \
-DPACKAGE_TESTS_DIR=\"$(top_srcdir)/src/tests/\" \
-DPACKAGE_BUILD_DIR=\"`pwd`/$(top_builddir)/src/tests/\" \
@EFL_CFLAGS@ \
@CHECK_CFLAGS@
engineer_tests_LDADD = @CHECK_LIBS@ $(top_builddir)/src/lib/libengineer.la
engineer_tests_DEPENDENCIES = $(top_builddir)/src/lib/libengineer.la

endif

EXTRA_DIST = test_engineer.c
