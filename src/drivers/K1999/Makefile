##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:28:27 CET 2000
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


ROBOT = K1999

SOLIBRARY = ${ROBOT}.so

SOLIBDIR  = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp

DATADIR   = drivers/${ROBOT}

DATA      = ${ROBOT}.xml settings.xml logo.rgb cg-nascar-rwd.rgb

# Mandatory Line Do Not Remove 
include ${MAKE_DEFAULT}

distrib:
	cd ..; tar -cvf K1999.tar K1999/{K1999.cpp,K1999.xml,settings.xml,skin.png,Makefile,logo.png}; gzip --best K1999.tar



