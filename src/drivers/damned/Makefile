##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:08:42 CET 2000
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

ROBOT = damned

MODULE    = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp

DATADIR   = drivers/${ROBOT}

DATA      = ${ROBOT}.xml car1.xml

DATASUBDIRS = 1 2 3 4 5 6 7 8 9 10

PKGSUBDIR	= $(DATASUBDIRS)

e-robots_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

e-robots_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


