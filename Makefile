##############################################################################
#
#    file                 : Makefile
#    created              : Mon Dec 11 22:30:53 CET 2000
#    copyright            : (C) 2000 by Eric Espié                        
#    email                : Eric.Espie@torcs.org   
#    version              : $Id$                                  
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################


# #### The Open Racing Car Simulator ####

ifndef TORCS_BASE

TORCS_BASE = $(shell pwd)
MAKE_DEFAULT = ${TORCS_BASE}/Make-default.mk
TORCS_RC = ${HOME}/.torcs.rc

-include Make-config

restart:
	@echo "TORCS_BASE = ${TORCS_BASE}" > ${TORCS_RC}
	@echo "MAKE_DEFAULT = ${MAKE_DEFAULT}" >> ${TORCS_RC}
	${MAKE} TORCS_BASE=${TORCS_BASE} MAKE_DEFAULT=${MAKE_DEFAULT}

endif

ifndef MAKE_DEFAULT

MAKE_DEFAULT = ${TORCS_BASE}/Make-default.mk

-include Make-config

restart2:
	${MAKE} TORCS_BASE=${TORCS_BASE} MAKE_DEFAULT=${MAKE_DEFAULT}

endif

PKGLIST		= src \
		  src-robots-base src-robots-berniw src-robots-K1999 \
		  data \
		  data-cars-extra \
		  data-cars-Patwo-Design \
		  data-cars-VM \
		  data-cars-nascar \
		  data-cars-kcendra-gt \
		  data-cars-kcendra-sport \
		  data-cars-kcendra-roadsters \
		  data-tracks-base data-devel \
		  src-robots-astigot \
		  src-robots-billy

DATASUBDIRS	= data

SHIPSUBDIRS	= src

SHIPEXECSUBDIRS	= src

EXPINCDIRS	= src

TOOLSUBDIRS	= src

SUBDIRS		= src

DATADIR 	= .

DATA    	= CHANGELOG.html COPYING Ticon.png Ticon.ico tux.png logo-skinner.png

SHIPEXECDIR	= .

SHIPEXEC	= setup_linux.sh

PKGSUBDIRS	= src data

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print | grep -v TAGS | grep -v torcstune.jar)

src_PKGDIR	= ${PACKAGE}-${VERSION}

-include ${MAKE_DEFAULT}

Make-config: configure Make-config.in
	rm -f config.status config.log config.cache
	./configure
	rm -f config.status config.log config.cache

configure: configure.in aclocal.m4
	rm -f config.status config.log config.cache
	autoconf

aclocal.m4: acinclude.m4
	aclocal

distclean: clean
	rm -f config.status config.log config.cache
	rm -f setup_linux.sh
	rm -rf ${EXPORTBASE}
	rm -rf ${PACKAGESBASE}/*
	rm -rf ${SPECFILESBASE}/*

cleanconfig: clean
	rm -f config.status config.log config.cache
	rm -f Make-config configure aclocal.m4

doc:
	rm -rf ${DOCBASE}/manual/api/*.html
	mkdir -p ${DOCBASE}/manual/api
	doxygen ${SOURCEBASE}/doc/torcsdoc.conf

tags:
	rm -f ${TORCS_BASE}/TAGS
	find ${TORCS_BASE}/src -name '*.h' -exec etags -a {} \;
	find /usr/include/plib -name '*.h' -exec etags -a {} \;
	find ${TORCS_BASE}/src -name '*.cpp' -exec etags -a {} \;
	find ${TORCS_BASE}/src -name '*.c' -exec etags -a {} \;

setup_linux.sh: linuxsetup
	@chmod +x setup_linux.sh
