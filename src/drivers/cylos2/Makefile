#
# Cylos Driver
#
# @(#) $Id$
#

ROBOT = cylos2

MODULE    = ${ROBOT}.so

MODULEDIR = drivers/${ROBOT}

SOURCES   = ${ROBOT}.cpp common.cpp

SHIPDIR   = drivers/${ROBOT}

SHIP      = ${ROBOT}.xml car1.xml cg-nascar-rwd.rgb logo.rgb

SHIPSUBDIRS = $(shell find * -maxdepth 0 -type d -print | grep -v CVS)

#PKGSUBDIRS		= ${SHIPSUBDIRS}

#src-robots-base_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

#src-robots-base_PKGDIR	= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


