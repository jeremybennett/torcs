#
#
#
# @(#) $Id$
#


SHIPDIR   = drivers/cylos1/tracksdata

SHIP      = $(shell find *.xml -maxdepth 0 -type f -print)

src-robots-cg_PKGFILES	= $(shell find * -maxdepth 0 -type f -print)

src-robots-cg_PKGDIR		= ${PACKAGE}-${VERSION}/$(subst ${TORCS_BASE},,$(shell pwd))

include ${MAKE_DEFAULT}


