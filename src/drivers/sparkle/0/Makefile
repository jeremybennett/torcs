##############################################################################
#
#    file                 : Makefile
#    created              : Wed Jan 8 18:31:16 CET 2003
#    copyright            : (C) 2002 Bernhard Wymann
#    email                : berniw@bluewin.ch
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

ROBOT       = sparkle
SHIPDIR     = drivers/${ROBOT}/0
SHIP        = baja-bug.rgb default.xml
SHIPSUBDIRS =

PKGSUBDIRS  = ${SHIPSUBDIRS}
src-robots-berniw_PKGFILES = $(shell find * -maxdepth 0 -type f -print)
src-robots-berniw_PKGDIR   = ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))
include ${MAKE_DEFAULT}


