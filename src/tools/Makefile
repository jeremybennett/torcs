##############################################################################
#                                   tools                     
#                             -------------------                                         
#    created              : Fri Aug 13 22:53:58 CEST 1999
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



TOOLSUBDIRS   = launcher

SUBDIRS	      = $(shell find * -maxdepth 0 -type d -print | grep -v CVS | grep -v $(TOOLSUBDIRS))

PKGSUBDIRS     = $(TOOLSUBDIRS) $(SUBDIRS)

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


