DIST_SUBDIRS=etc m4 include cjeca32 ifd libcyberjack doc

SUBDIRS=m4 include cjeca32

if IS_LINUX
SUBDIRS+=etc
endif


ACLOCAL_AMFLAGS=-I m4

#SUBDIRS+=ifd libcyberjack checksuite tools debian doc
SUBDIRS+=ifd libcyberjack tools doc


EXTRA_DIST=\
  ifd-cyberjack.spec.in ifd-cyberjack.spec \
  COPYRIGHT.GPL COPYRIGHT.LGPL \
  ChangeLog ChangeLog.old

rpm:    ifd-cyberjack.spec dist
	rpmbuild="rpm" && \
	if [ `rpm --version | awk '{ print $$3 }'` > /dev/null ]; then rpmbuild="rpmbuild"; fi && \
	$$rpmbuild -ta ifd-cyberjack-$(VERSION).tar.gz

ChangeLog:
	git log --pretty="format:------------------------------------------------------------------%n%ai %an%n%s%n%b" >ChangeLog


#dist-hook:
#	rm -f ChangeLog 2>/dev/null
#	$(MAKE) ChangeLog

