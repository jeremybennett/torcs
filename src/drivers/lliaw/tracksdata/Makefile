##############################################################################
#
#    file                 : Makefile
#    created              : Sat Oct 30 19:53:08 CEST 1999
#    copyright            : (C) 1999 by Eric Espie                         
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


DATADIR   = drivers/lliaw/tracksdata

DATA      = $(shell find . -name '*.xml' -maxdepth 1 -type f -print)

e-robots_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

e-robots_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


