
EXTRA_DIST=Info.plist.in PkgInfo ifd_special.cpp

AM_CFLAGS=$(visibility_cflags)
AM_CPPFLAGS=$(visibility_cflags)


noinst_HEADERS=\
  ctbcs.h ifd.h cyberjack_l.h

INCLUDES=-I$(top_srcdir)/include -I../include/driver -I../include/firmware -I.. -I../cjeca32 -I.. -I../cjeca32/ausb $(pcsc_includes)

bundledir=$(usbdropdir)/libifd-cyberjack.bundle/Contents
bundle_DATA=Info.plist PkgInfo

if IS_LINUX
bundlelinuxdir=$(usbdropdir)/libifd-cyberjack.bundle/Contents/Linux
bundlelinux_LTLIBRARIES=libifd-cyberjack.la
endif

if IS_OSX
bundleosxdir=$(usbdropdir)/libifd-cyberjack.bundle/Contents/MacOS
bundleosx_LTLIBRARIES=libifd-cyberjack.la
endif

libifd_cyberjack_la_SOURCES=ifd.cpp
libifd_cyberjack_la_LDFLAGS=-version-info @CYBERJACK_SO_CURRENT@:@CYBERJACK_SO_REVISION@:@CYBERJACK_SO_AGE@ -no-undefined
#libifd_cyberjack_la_LIBADD=$(top_builddir)/cjeca32/libeca.la $(top_builddir)/cjeca32/ausb/libausb.la
libifd_cyberjack_la_LIBADD=$(top_builddir)/cjeca32/libeca.la -lstdc++

