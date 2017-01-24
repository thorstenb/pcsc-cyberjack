DIST_SUBDIRS=ausb

if ENABLE_NONSERIAL
SUBDIRS=ausb
endif


INCLUDES=-I../include -I../include/driver -I../include/firmware -Iausb $(pcsc_includes)


AM_CFLAGS=$(visibility_cflags) @cyberjack_platform_def@ \
  -DBUILDING_CYBERJACK \
  -DCYBERJACK_CONFIG_FILE=\"@cyberjack_config_file@\"
  
AM_CPPFLAGS=$(visibility_cflags) @cyberjack_platform_def@ \
  -DBUILDING_CYBERJACK \
  -DCYBERJACK_CONFIG_FILE=\"@cyberjack_config_file@\"



noinst_HEADERS=\
  BaseCommunication.h \
  BaseReader.h \
  BaseTranslater.h \
  CCIDReader.h \
  EC30Reader.h \
  ECAReader.h \
  ECBReader.h \
  ECFReader.h \
  ECPReader.h \
  ECRReader.h \
  ECMReader.h \
  EFBReader.h \
  PPAReader.h \
  RSCTCriticalSection.h \
  RFKReader.h \
  RFSReader.h \
  RFSoliReader.h \
  RFCReader.h \
  CPTReader.h \
  CGOReader.h \
  WAVReader.h \
  SerialUnix.h \
  SECReader.h \
  SYOReader.h \
  TLSReader.h \
  BDRReader.h \
  SHUReader.h \
  SISReader.h \
  USBUnix.h \
  ccid.h \
  config_l.h config_p.h \
  ntstatus.h \
  stdafx.h \
  version.h \
  PCSC10.h

noinst_LTLIBRARIES=libeca.la
libeca_la_SOURCES=\
  BaseCommunication.cpp \
  BaseReader.cpp \
  BaseTranslater.cpp \
  CCIDReader.cpp \
  Debug.cpp \
  EC30Reader.cpp \
  ECAReader.cpp \
  ECBReader.cpp \
  ECFReader.cpp \
  ECPReader.cpp \
  ECRReader.cpp \
  ECMReader.cpp \
  EFBReader.cpp \
  PPAReader.cpp \
  RSCTCriticalSection.cpp \
  RFKReader.cpp \
  RFSReader.cpp \
  RFSoliReader.cpp \
  RFCReader.cpp \
  CPTReader.cpp \
  CGOReader.cpp \
  WAVReader.cpp \
  Reader.cpp \
  USBUnix.cpp \
  SerialUnix.cpp \
  SECReader.cpp \
  SYOReader.cpp \
  TLSReader.cpp \
  BDRReader.cpp \
  SHUReader.cpp \
  SISReader.cpp \
  cjeca32.cpp \
  Platform_unix.cpp \
  config.cpp


if ENABLE_NONSERIAL
libeca_la_LIBADD=ausb/libausb.la 
endif


