##############################################################################
#
#    file                 : Makefile
#    created              : Sun Jan 30 22:42:54 CET 2000
#    copyright            : (C) 2000 by Eric Espie                         
#    email                : torcs@free.fr   
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


SUBDIRS     = $(shell find * -maxdepth 0 -type d -print | grep -v CVS)

SHIPSUBDIRS = $(SUBDIRS)

PKGSUBDIRS	= $(SUBDIRS)

src_PKGFILES	= Makefile

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


