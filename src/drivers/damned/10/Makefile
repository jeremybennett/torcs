##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:14:45 CET 2000
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


ROBOT = damned

DATADIR   = drivers/${ROBOT}/10

DATA      =  car.xml logo.rgb 155-DTM.rgb

e-robots_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

e-robots_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


