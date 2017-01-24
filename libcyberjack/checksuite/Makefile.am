
noinst_LTLIBRARIES=libchecksuite.la

DEFS+=-DCD_SCRIPT_DIR=\"$(libdir)/cyberjack\"

AM_CXXFLAGS=@cyberjack_platform_def@ \
  -DBUILDING_CYBERJACK

INCLUDES= $(pcsc_includes) \
          -I$(top_srcdir)/include \
	  -I../../include/driver \
	  -I../../include/firmware \
	  -I../.. -I../../cjeca32 -I../.. -I../../cjeca32/ausb \
	  -I../../libcyberjack \
	  -I../../ifd


libchecksuite_la_SOURCES=\
  cm_distri.cpp \
  cm_group.cpp \
  cm_reader.cpp \
  cm_services.cpp \
  cm_uname.cpp \
  checkmodule.cpp \
  checksuite.cpp

noinst_HEADERS=\
  cm_distri.h \
  cm_group.h \
  cm_reader.h \
  cm_services.h \
  cm_uname.h \
  checkmodule.h \
  checksuite.h

