##############################################################################
#
#    file        : Makefile
#    created     : Mon Nov 11 11:54:13 CET 2002
#    copyright   : (C) 2002 by Eric Espié                        
#    email       : Eric.Espie@torcs.org   
#    version     : $Id$                                  
#
##############################################################################
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
##############################################################################

ROBOT     = inferno6

MODULE    = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp common.cpp

SHIPDIR   = drivers/${ROBOT}

SHIP      = ${ROBOT}.xml car1.xml logo.rgb porsche-gt3rs.rgb

SHIPSUBDIRS = $(shell find * -maxdepth 0 -type d -print | grep -v CVS)

PKGSUBDIRS		= ${SHIPSUBDIRS}

src-robots-base_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src-robots-base_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


