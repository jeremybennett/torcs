##############################################################################
#
#    file                 : Makefile
#    created              : Sun Jan 30 22:42:20 CET 2000
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


MODULE    = quickrace.so

MODULEDIR = modules/raceman

SOURCES   = quickrace.cpp qracemain.cpp qracegl.cpp qrmenu.cpp

SHIPDIR   = config/quickrace

SHIP      = qrace.xml

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


