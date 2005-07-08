##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:31:47 CET 2000
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


SHIPSUBDIRS	= tgf tgfclient raceengineclient learning

EXPINCDIRS	= txml tgf tgfclient client confscreens racescreens robottools raceengineclient learning \
			  portability

TOOLSUBDIRS	= txml

SUBDIRS		= confscreens racescreens robottools txml tgf tgfclient client raceengineclient learning \
			  portability

PKGSUBDIRS	= $(SUBDIRS)

src_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))


include ${MAKE_DEFAULT}


