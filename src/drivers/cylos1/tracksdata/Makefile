#
#
#
# @(#) $Id$
#


SHIPDIR   = drivers/cylos1/tracksship

SHIP      = $(shell find *.xml -maxdepth 0 -type f -print)

g-robots_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

g-robots_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


