##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:28:27 CET 2000
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

ROBOT = K1999

MODULE    = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp

DATADIR   = drivers/${ROBOT}

DATA      = ${ROBOT}.xml logo.rgb

DATASUBDIRS = 1 2

PKGSUBDIRS	= $(DATASUBDIRS)

K1999-robots_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

K1999-robots_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}
