##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:18:59 CET 2000
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


ROBOT = lliaw

MODULE    = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp

SHIPDIR   = drivers/${ROBOT}

SHIP      = ${ROBOT}.xml car.xml viper-gts-r.rgb logo.rgb

SHIPSUBDIRS = $(shell find * -maxdepth 0 -type d -print | grep -v CVS)

PKGSUBDIRS		= ${SHIPSUBDIRS}

src-robots-e_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src-robots-e_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


