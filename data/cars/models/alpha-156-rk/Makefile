##############################################################################
#
#    file                 : Makefile
#    created              : Wed Sep 11 22:04:04 CEST 2002
#    copyright            : (C) 2002 by Eric Espié                        
#    email                : Eric.Espie@torcs.org   
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

DATADIR   = cars/alpha-156-rk

DATA      = $(shell find *.xml -maxdepth 0 -type f -print) \
	    $(shell find *.rgb -maxdepth 0 -type f -print) \
	    $(shell find *.acc -maxdepth 0 -type f -print)  \
	    $(shell find *.txt -maxdepth 0 -type f -print)

data-cars-Ryuji-Kainoh_PKGFILES	= $(DATA) $(shell find *.ac -maxdepth 0 -type f -print)

data-cars-Ryuji-Kainoh_PKGDIR	= $(DATADIR)


include ${MAKE_DEFAULT}


