##############################################################################
#
#    file                 : Makefile
#    created              : Mon Nov 13 21:48:27 CET 2000
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


PROGRAM   = texmapper

SOURCES   = texmapper.cpp ssgSaveAC.cpp

SOLIBS    = -lplibssg -lplibsg -lplibul -ltgf -ltgfclient -ltxml -lpng

src-tools_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src-tools_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))


include ${MAKE_DEFAULT}
