SUBDIRS=checksuite libdialog

INCLUDES= $(pcsc_includes) $(libxml2_includes) \
          -I../include -I../include/driver -I../ifd -I../libcyberjack -I../cjeca32 -I../include/firmware -Iausb

#AM_CFLAGS=$(visibility_cflags) @cyberjack_platform_def@
#AM_CPPFLAGS=$(visibility_cflags) @cyberjack_platform_def@

AM_CFLAGS=@cyberjack_platform_def@
AM_CPPFLAGS=@cyberjack_platform_def@

noinst_LTLIBRARIES=libcyberjack.la
libcyberjack_la_SOURCES=\
  driver.cpp \
  driver_pcsc.cpp \
  module.cpp \
  mtemplate.cpp \
  modulestore.cpp


if ENABLE_NONSERIAL
libcyberjack_la_LIBADD=\
 ../cjeca32/ausb/libausb.la \
 -lstdc++ @THREAD_LIBS@ $(hal_libs) $(pcsc_libraries) $(pcsc_lib) $(libusb_LIBS)
else
libcyberjack_la_LIBADD=\
 -lstdc++ @THREAD_LIBS@ $(pcsc_libraries) $(pcsc_lib)
endif

if USE_XML2
libcyberjack_la_LIBADD+=$(libxml2_libs)
endif


libcyberjack_la_LDFLAGS=\
 -version-info @CYBERJACK_SO_CURRENT@:@CYBERJACK_SO_REVISION@:@CYBERJACK_SO_AGE@


noinst_HEADERS=\
  driver.hpp \
  driver_pcsc.hpp driver_pcsc_p.hpp \
  module.hpp mtemplate.hpp modulestore.hpp


noinst_PROGRAMS=libtest

libtest_SOURCES=libtest.cpp
libtest_LDADD=libcyberjack.la -ldl -lstdc++ $(pcsc_libraries) $(pcsc_lib) $(libusb_LIBS)
#libtest_LDFLAGS=-all-static
