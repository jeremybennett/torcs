##############################################################################
#
#    file                 : Make-default.mk
#    created              : Sat Mar 18 23:53:11 CET 2000
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

ifndef TORCS_BASE

-include ${HOME}/.torcs

ifndef TORCS_BASE

error:
	@echo "TORCS_BASE should be defined"
	@exit 1

endif
endif

-include ${TORCS_BASE}/Make-config

SOURCEBASE  = ${TORCS_BASE}/src
EXPORTBASE  = ${TORCS_BASE}/export
DOCBASE     = ${TORCS_BASE}/doc
INSTBASE    = ${DESTDIR}${instdir}
INSTBINBASE = ${DESTDIR}${bindir}
INSTLIBBASE = ${DESTDIR}${prefix}/lib


# win32
INIT_WIN32       = ${TORCS_BASE}/setup_win32.bat
INIT_WIN32_D     = ${TORCS_BASE}/setup_win32_debug.bat


define create_dir_win32
TotDir=`echo $$createdir | sed -e "s:${TORCS_BASE}/::g" ` ; \
CurDir='.' ; \
echo "" >> ${INIT_WIN32} ; \
for Dir in `echo $$TotDir | sed -e 's:/: :g' ` ; \
do CurDir=$$CurDir/$$Dir ; \
echo "call .\\create_dir $$CurDir" >> ${INIT_WIN32} ; \
done
endef


OB1 = $(SOURCES:.cpp=.o)
OBJECTS = $(OB1:.c=.o)

define recursedirs
for Dir in $$RecurseDirs ;\
do ${MAKE} -C $$Dir $$RecurseFlags TORCS_BASE=${TORCS_BASE} MAKE_DEFAULT=${MAKE_DEFAULT}; \
done
endef

COMPILATION=
ifdef LIBRARY
COMPILATION=true
endif
ifdef PROGRAM
COMPILATION=true
endif
ifdef MODULE
COMPILATION=true
endif
ifdef SOLIBRARY
COMPILATION=true
endif
ifdef TOOLS
COMPILATION=true
endif


ifdef COMPILATION

default: win32start exports tools compil win32end

ifeq (.depend,$(wildcard .depend))
include .depend
endif

.depend:
	$(CPP) $(INCFLAGS) $(CFLAGSD)  $(SOURCES) > .depend

dep:	.depend

compil: subdirs ${LIBRARY} ${SOLIBRARY} ${MODULE} ${PROGRAM} dep

else

default: win32start exports tools subdirs win32end

compil: subdirs ${LIBRARY} ${SOLIBRARY} ${MODULE} ${PROGRAM}

endif

win32start:
	@rm -f ${INIT_WIN32}
	@echo '@echo off' > ${INIT_WIN32}
	@echo 'echo Checking directories ...' >> ${INIT_WIN32}
	@echo '' >> ${INIT_WIN32}


win32end:
	@sed -e "s:${TORCS_BASE}:\.:g" ${INIT_WIN32} > ${INIT_WIN32}.eee
	@mv ${INIT_WIN32}.eee ${INIT_WIN32}
	@sed -e "s:/src/linux/:/src/windows/:g" ${INIT_WIN32} > ${INIT_WIN32}.eee
	@mv ${INIT_WIN32}.eee ${INIT_WIN32}
	@sed -e "s:/:\\\:g" ${INIT_WIN32} > ${INIT_WIN32}.eee
	@mv ${INIT_WIN32}.eee ${INIT_WIN32}
	@sed -e "s:runtime:runtimed:g" ${INIT_WIN32} > ${INIT_WIN32_D}


.PHONY : clean tools toolsdirs subdirs expincdirs exports export compil cleantools cleancompil datadirs doc win32start win32end

# Recursive targets

exports: expincdirs export

tools: toolsdirs ${TOOLS} toolsdata

clean: cleancompil cleantools
	-rm -f ${LIBRARY} ${OBJECTS} ${PROGRAM} .depend ${SOLIBRARY} ${MODULE} ${GARBAGE} *~

cleantools: cleantoolsdirs
	-rm -f  ${TOOLS} .depend ${GARBAGE} *~

cleancompil: cleansubdirs
	-rm -f ${LIBRARY} ${OBJECTS} ${PROGRAM} .depend ${SOLIBRARY} ${MODULE} ${GARBAGE} *~

install: installdirs installdata installsolibrary installmodule installprogram installtools installtoolsdata win32end


.SUFFIXES: .cpp

.cpp.o:
	${CXX} $(INCFLAGS) $(CXXFLAGS) $(COMPILFLAGS) -c $<

.SUFFIXES: .c

.c.o:
	${CC} $(INCFLAGS) $(CFLAGS) $(COMPILFLAGS) -c $<



ifdef LIBRARY

${LIBRARY}: ${OBJECTS}
	${AR} ${ARFLAGS} ${LIBRARY} ${OBJECTS}
	${RANLIB} ${LIBRARY}
	${STRIP} ${LIBRARY}
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${LIBDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${LIBRARY}" ; \
	echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X

endif

ifdef DATA

installdata: $(DATA)
	@D=`pwd` ; \
	createdir="runtime/${DATADIR}" ; \
	${create_dir_win32} ; \
	createdir="${INSTBASE}/${DATADIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	for X in $? ; \
	do echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X ; \
	echo "copy $$D/$$X ./runtime/${DATADIR}/$$X" >> ${INIT_WIN32} ; \
	done

else

installdata: ;

endif

ifdef EXPORTS

export: $(EXPORTS)
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${EXPDIR}" ;\
	$(mkinstalldirs) $$createdir ; \
	${create_dir_win32} ; \
	for X in $? ; \
	do echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X ; \
	echo "copy $$D/$$X $$createdir/$$X" >> ${INIT_WIN32} ; \
	done

else

export: ;

endif



ifdef PROGRAM

${PROGRAM}: ${OBJECTS} $(subst -l,${EXPORTBASE}/lib/lib, ${LIBS:=.a})
	${CXX} ${OBJECTS} ${LDFLAGS} ${LIBS} ${EXT_LIBS} ${SOLIBS} -o $@
	${STRIP} $@

installprogram: ${PROGRAM}
	@ createdir="${INSTBASE}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${PROGRAM}" ; \
	echo " $(INSTALL_PROGRAM) $$X $$createdir/$$X"; \
	$(INSTALL_PROGRAM) $$X $$createdir/$$X

else

installprogram: ;

endif

ifdef TOOLS

${TOOLS}: ${OBJECTS} $(subst -l,${EXPORTBASE}/lib/lib, ${LIBS:=.a})
	${CXX} ${OBJECTS} ${LDFLAGS} ${LIBS} ${EXT_LIBS} ${SOLIBS} -o $@
	${STRIP} $@

installtools: ${TOOLS}
	@createdir="${INSTBINBASE}/${TOOLSDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${TOOLS}" ; \
	echo " $(INSTALL_PROGRAM) $$X $$createdir/$$X"; \
	$(INSTALL_PROGRAM) $$X $$createdir/$$X

else

ifdef TOOLSCRIPT

installtools: ${TOOLSCRIPT}
	@createdir="${INSTBINBASE}/${TOOLSDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${TOOLSCRIPT}" ; \
	echo " $(INSTALL_PROGRAM) $$X $$createdir/$$X"; \
	$(INSTALL_PROGRAM) $$X $$createdir/$$X

else

installtools: ;

endif
endif

ifdef TOOLSDATA

toolsdata: ;

installtoolsdata: $(TOOLSDATA)
	@createdir="${INSTBASE}/${TOOLSDATADIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	for X in $? ; \
	do echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X ; \
	done


else 

toolsdata: ;
installtoolsdata: ;

endif


ifdef SOLIBRARY

${SOLIBRARY}: ${OBJECTS}
	${CXX} -shared -o ${SOLIBRARY} ${OBJECTS} ${LIBSPATH} ${LIBS} 
	${STRIP} ${SOLIBRARY}
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/lib" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${SOLIBRARY}" ; \
	echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X


installsolibrary: ${SOLIBRARY}
	@createdir="runtime/${SOLIBDIR}" ; \
	${create_dir_win32} ; \
	createdir="${INSTLIBBASE}" ; \
	X="${SOLIBRARY}" ;\
	$(mkinstalldirs) $$createdir ; \
	echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X


else

installsolibrary: ;

endif

ifdef MODULE

${MODULE}: ${OBJECTS}
	${CXX} -shared -o ${MODULE} ${OBJECTS} ${LIBSPATH} ${LIBS} 
	${STRIP} ${MODULE}
	@D=`pwd` ; \
	createdir="${EXPORTBASE}/${MODULEDIR}" ; \
	$(mkinstalldirs) $$createdir ; \
	X="${MODULE}" ; \
	echo " Exporting $$X to $$createdir/$$X"; \
	ln -sf $$D/$$X $$createdir/$$X


installmodule: ${MODULE}
	@createdir="runtime/${MODULEDIR}" ; \
	${create_dir_win32} ; \
	createdir="${INSTBASE}/${MODULEDIR}" ; \
	X="${MODULE}" ;\
	$(mkinstalldirs) $$createdir ; \
	echo " $(INSTALL_DATA) $$X $$createdir/$$X"; \
	$(INSTALL_DATA) $$X $$createdir/$$X


else

installmodule: ;

endif

ifdef DATASUBDIRS

instdatadirs:
	@RecurseDirs="${DATASUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

else

instdatadirs: ;

endif


ifdef EXPINCDIRS

expincdirs: 
	@RecurseDirs="${EXPINCDIRS}" ; \
	RecurseFlags="exports" ; \
	${recursedirs}

else

expincdirs: ;

endif



ifdef SUBDIRS

subdirs: 
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="compil" ; \
	${recursedirs}

cleansubdirs:
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="cleancompil" ; \
	${recursedirs}

instsubdirs:
	@RecurseDirs="${SUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

else

subdirs: ;
cleansubdirs: ;
instsubdirs: ;

endif



ifdef TOOLSUBDIRS

toolsdirs: 
	@RecurseDirs="${TOOLSUBDIRS}" ; \
	RecurseFlags="tools" ; \
	${recursedirs}

cleantoolsdirs:
	@RecurseDirs="${TOOLSUBDIRS}" ; \
	RecurseFlags="cleantools" ; \
	${recursedirs}

insttoolsdirs:
	@RecurseDirs="${TOOLSUBDIRS}" ; \
	RecurseFlags="install" ; \
	${recursedirs}

else

toolsdirs: ;
cleantoolsdirs: ;
insttoolsdirs: ;

endif

ifdef INITSUBDIRS

initsubdirs:
	@RecurseDirs="${INITSUBDIRS}" ; \
	RecurseFlags="init" ; \
	${recursedirs}

endif

#to be done in a better way...
ifdef SRCDOC

info:
	mkdir -p ${DOCBASE}/manual/api
	doxygen ${SOURCEBASE}/doc/torcsdoc.conf

endif


installdirs:
	@if [ -n "${DATASUBDIRS}" ] || [ -n "${SUBDIRS}" ] || [ -n "${TOOLSUBDIRS}" ] ; \
	then R=`for I in ${DATASUBDIRS} ${SUBDIRS} ${TOOLSUBDIRS} ; \
	do echo $$I ;\
	done | sort -u` ; \
	RecurseDirs="$$R" ; \
	RecurseFlags="install" ; \
	${recursedirs} ; \
	fi
