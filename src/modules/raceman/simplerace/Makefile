##############################################################################
#
#    file        : Makefile
#    created     : Sat Nov 16 17:48:40 CET 2002
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


MODULE    = simplerace.so

MODULEDIR = modules/raceman

SOURCES   = simpleconfig.cpp simplehook.cpp simplerace.cpp

SHIPDIR   = config/simplerace

SHIP      = simplerace.xml

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


