##############################################################################
#
#    file        : Makefile
#    created     : Wed Nov  3 20:31:16 CET 2004
#    copyright   : (C) 2004 by Eric Espié                        
#    email       : Eric.Espie@free.fr   
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


SOLIBRARY    = liblearning.so

SOLIBDIR     = .

SOURCES      = policy.cpp

EXPORTS      = policy.h

EXPDIR       = include

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))


include ${MAKE_DEFAULT}


