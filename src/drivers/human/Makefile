##############################################################################
#
#    file                 : Makefile
#    created              : Sat Mar 18 23:15:13 CET 2000
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


ROBOT = human

MODULE    = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

LIBS      =  -lplibul

SOURCES   = ${ROBOT}.cpp pref.cpp

DATADIR   = drivers/${ROBOT}

DATA      = $(shell find *.xml -maxdepth 0 -type f -print) $(shell find *.rgb -maxdepth 0 -type f -print)


DATASUBDIRS = cg-gt-rwd tracks mclaren-f1

include ${MAKE_DEFAULT}


