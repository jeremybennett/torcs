##############################################################################
#
#    file        : Makefile
#    created     : Sun Jan  5 10:11:19 CET 2003
#    copyright   : (C) 2003 by Eric Espié                        
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


SHIPDIR   = config/raceman

SHIP      = $(shell find * -maxdepth 0 -name '*.xml' -print)

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))




include ${MAKE_DEFAULT}


