/***************************************************************************
                 params.cpp -- configuration parameters management                                     
                             -------------------                                         
    created              : Fri Aug 13 22:27:57 CEST 1999
    copyright            : (C) 1999 by Eric Espie                         
    email                : torcs@free.fr   
    version              : $Id$                                  
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

/** @file   
    		This is the parameters manipulation API.
    		The parameters are stored in XML files and accessed only with this API.
		<br>The parameters are structured in:
		<br><b>section</b> - containing a familly of parameters on the same topic.
		<br><b>list</b> - containing <b>elements</b>
		<br>of <b>numerical attributes</b> and <b>string attributes</b>.
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	params
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <math.h>

#include <xmlparse.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>

#include "params.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

/* All the lists are organized circularly */
/* and the pointer is on the last element */
static tParm *TheParms = (tParm*)NULL;

static tParm		*CurParm;
static tParmNode	*TheCurNode;

void
gfParamInit(void)
{
}

static int
mystrcmp(const void *s1, const void * s2)
{
    return strcmp((const char *)s1, (const char *)s2);
}

static void
gfParmAddKid(tParmNode *node, tParmNode *newNode)
{
    if (node->type & PARM_NODE_BRANCH) {
	if (node->kids == NULL) {
	    node->kids = newNode;
	    newNode->next = newNode;
	    newNode->prev = newNode;
	} else {
	    newNode->next = node->kids;
	    newNode->prev = newNode->next->prev;
	    newNode->next->prev = newNode;
	    newNode->prev->next = newNode;
	}
	newNode->parent = node;
    } else {
	GfTrace3("file: %s -> Grammar Error %s not allowed in %s\n", CurParm->file, newNode->name, node->name);
	GfParmReleaseHandle((void*)CurParm);
	exit(1);
    }
}


/*
 * Function
 *	startElement
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void 
startElement(void * /* userData */, const char *name, const char **atts)
{
    int		nAtts;
    const char	**p;
    const char	*s1, *s2;
    char	*stk, *stk1;
    char	*unit;
    int		minflg, maxflg, found;
    tParmWithin	*curWithin;

    p = atts;
    while (*p)
	++p;
    nAtts = (p - atts) >> 1;
    if (nAtts > 1) {
	qsort((void *)atts, nAtts, sizeof(char *) * 2, mystrcmp);
    }

    if (!strcmp(name, "params")) {
	TheCurNode = (tParmNode*)calloc(1, sizeof(tParmNode));
	CurParm->n.kids = TheCurNode;
	TheCurNode->type = PARM_NODE_PARM;
	TheCurNode->next = TheCurNode;
	TheCurNode->prev = TheCurNode;
	TheCurNode->parent = (tParmNode*)CurParm;
	while (*atts) {
	    s1 = *atts++;
	    s2 = *atts++;
	    if (!strcmp(s1, "name")) {
		TheCurNode->name = strdup(s2);
	    }
	    if (!strcmp(s1, "type")) {
		if (!strcmp(s2, GFPARM_TEMPL_STR)) {
		    CurParm->type = GFPARM_TEMPLATE;
		} else {
		    CurParm->type = GFPARM_PARAMETER;
		}
	    }
	    if (!strcmp(s1, "mode")) {
		if (strchr(s2, 'M') || strchr(s2, 'm')) {
		    CurParm->mode |= GFPARM_MODIFIABLE;
		}
		if (strchr(s2, 'W') || strchr(s2, 'w')) {
		    CurParm->mode |= GFPARM_WRITABLE;
		}
	    }
	}
    }
    
    if (!strcmp(name, "section")) {
	tParmSect *cursect = (tParmSect*)calloc(1, sizeof(tParmSect));

	cursect->n.type = PARM_NODE_SECT;
	gfParmAddKid(TheCurNode, (tParmNode*)cursect);
	TheCurNode = (tParmNode*)cursect;
	
	while (*atts) {
	    s1 = *atts++;
	    s2 = *atts++;
	    if (!strcmp(s1, "name")) {
		cursect->n.name = strdup(s2);
	    }
	}
    }
    
    
    if (!strcmp(name, "attnum")) {
	tParmKey *curkey = (tParmKey*)calloc(1, sizeof(tParmKey));

	curkey->n.type = PARM_NODE_KEY;
	gfParmAddKid(TheCurNode, (tParmNode*)curkey);
	TheCurNode = (tParmNode*)curkey;
	
	unit = (char*)NULL;
	minflg = maxflg = 0;
	curkey->type = P_NUM;
	while (*atts) {
	    s1 = *atts++;
	    s2 = *atts++;
	    if (!strcmp(s1, "name")) {
		curkey->n.name = strdup(s2);
	    }
	    if (!strcmp(s1, "unit")) {
		unit = strdup(s2);
	    }
	    if (!strcmp(s1, "val")) {
		if (strncasecmp(s2, "0x", 2) == 0) {
		    curkey->valnum = (tdble)strtoul(s2, (char**)NULL, 0);
		} else {
		    curkey->valnum = (tdble)strtod(s2, (char**)NULL);
		}
	    }
	    if (!strcmp(s1, "min")) {
		minflg = 1;
		curkey->min = (tdble)strtod(s2, (char**)NULL);
	    }
	    if (!strcmp(s1, "max")) {
		maxflg = 1;
		curkey->max = (tdble)strtod(s2, (char**)NULL);
	    }
	}
	if (minflg == 0) {
	    curkey->min = curkey->valnum;
	}
	if (maxflg == 0) {
	    curkey->max = curkey->valnum;
	}
	if (unit) {
	    curkey->valnum = GfParmUnit2SI(unit, curkey->valnum);
	    curkey->min = GfParmUnit2SI(unit, curkey->min);
	    curkey->max = GfParmUnit2SI(unit, curkey->max);
	    free(unit);
	}
	if (curkey->min > curkey->valnum) {
	    curkey->min = curkey->valnum;
	}
	if (curkey->max < curkey->valnum) {
	    curkey->max = curkey->valnum;
	}
    }
    
    if (!strcmp(name, "attstr")) {
	tParmKey *curkey = (tParmKey*)calloc(1, sizeof(tParmKey));

	curkey->n.type = PARM_NODE_KEY;
	gfParmAddKid(TheCurNode, (tParmNode*)curkey);
	TheCurNode = (tParmNode*)curkey;

	curkey->type = P_STR;
	while (*atts) {
	    s1 = *atts++;
	    s2 = *atts++;
	    if (!strcmp(s1, "name")) {
		curkey->n.name = strdup(s2);
	    }
	    if (!strcmp(s1, "val")) {
		curkey->valstr = strdup(s2);
	    }
	    if (!strcmp(s1, "in")) {
		stk = strdup(s2);
		stk1 = strtok(stk, ",");
		while (stk1) {
		    curWithin = (tParmWithin*)calloc(1, sizeof(tParmWithin));
		    curWithin->val = strdup(stk1);
		    if (curkey->withins == NULL) {
			curkey->withins = curWithin;
			curWithin->next = curWithin;
		    } else {
			curWithin->next = curkey->withins->next;
			curkey->withins->next = curWithin;
			curkey->withins = curWithin;
		    }
		    stk1 = strtok((char*)NULL, ",");
		}
		free(stk);
	    }
	}
	found = 0;
	if (curkey->withins != NULL) {
	    curWithin = curkey->withins;
	    do {
		curWithin = curWithin->next;
		if (strcmp(curWithin->val, curkey->valstr) == 0) {
		    found = 1;
		    break;
		}
	    } while (curWithin != curkey->withins);
	}
	if (!found) {
	    curWithin = (tParmWithin*)calloc(1, sizeof(tParmWithin));
	    curWithin->val = strdup(curkey->valstr);
	    if (curkey->withins == NULL) {
		curkey->withins = curWithin;
		curWithin->next = curWithin;
	    } else {
		curWithin->next = curkey->withins->next;
		curkey->withins->next = curWithin;
		curkey->withins = curWithin;
	    }
	}
    }
}

/*
 * Function
 *	endElement
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 *
 * Remarks
 *	
 */
static void 
endElement(void * /* userData */, const char * /* name */)
{
    TheCurNode = TheCurNode->parent;
}

/*
 * Function
 *	
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	
 */
static int 
externalEntityRefHandler(XML_Parser mainparser,
			 const XML_Char *openEntityNames,
			 const XML_Char * /* base */,
			 const XML_Char *systemId,
			 const XML_Char * /* publicId */)
{
    FILE 	*in;
    char	buf[BUFSIZ];
    XML_Parser 	parser;
    int		done;

    parser = XML_ExternalEntityParserCreate(mainparser,
					    openEntityNames,
					    (const XML_Char *)NULL);

    in = fopen(systemId, "r");
    if (in == NULL) {
	perror(systemId);
	GfTrace1("GfReadParmFile: file %s has pb\n", systemId);
	return 0;
    }

    XML_SetElementHandler(parser, startElement, endElement);
    do {
	size_t len = fread(buf, 1, sizeof(buf), in);
	done = len < sizeof(buf);
	if (!XML_Parse(parser, buf, len, done)) {
	    GfTrace3("file: %s -> %s at line %d\n",
		     systemId,
		     XML_ErrorString(XML_GetErrorCode(parser)),
		     XML_GetCurrentLineNumber(parser));
	    GfParmReleaseHandle((void*)CurParm);
	    fclose(in);
	    return 0;
	}
    } while (!done);
    XML_ParserFree(parser);
    return 1;
}

static tParm *
gfCheckParmWithFile(const char *file, int mode, int *toload)
{
    /* Verify if the file has already been read */
    if (TheParms != NULL) {
	CurParm = TheParms; /* last element */
	do {
	    CurParm = (tParm*)CurParm->n.next;
	    if ((CurParm->file != NULL) && (strcmp(CurParm->file, file) == 0)) {
		if (!(mode & GFPARM_RMODE_REREAD)) {
		    CurParm->refcount++;
		    //GfOut("GfReadParmFile: file %s already loaded, use it (ref = %d)\n", file, CurParm->refcount);
		    *toload = 0;
		    return CurParm;
		} else {
		    //GfOut("GfReadParmFile: file %s already loaded, force reload (ref = %d)\n", file, CurParm->refcount);
		    GfParmClean((void*)CurParm);
		    *toload = 1;
		    return CurParm;
		}
	    }
	} while (CurParm != TheParms);
	//GfOut("GfReadParmFile: file %s not loaded, load (ref = 1)\n", file);
	CurParm = (tParm*)calloc(1, sizeof(tParm));
	CurParm->refcount = 1;
	CurParm->n.type = PARM_NODE_ROOT;
	CurParm->n.next = TheParms->n.next;
	CurParm->n.prev = (tParmNode*)TheParms;
	CurParm->n.next->prev = (tParmNode*)CurParm;
	CurParm->n.prev->next = (tParmNode*)CurParm;
	TheParms = CurParm;
    } else {
	//GfOut("GfReadParmFile: file %s not loaded, load (ref = 1)\n", file);
	CurParm = (tParm*)calloc(1, sizeof(tParm));
	CurParm->refcount = 1;
	CurParm->n.type = PARM_NODE_ROOT;
	CurParm->n.next = (tParmNode*)CurParm;
	CurParm->n.prev = (tParmNode*)CurParm;
	TheParms = CurParm;
    }
    *toload = 1;
    return CurParm;
}

/** Read a parameter file.
    @ingroup	params
    @param	file	Name of the parameter file
    @param	mode	GFPARM_RMODE_STD Open the parameter file only once
    			<br>GFPARM_RMODE_REREAD Force the re-read of the file and release the previous one
    @param	name	Receives the name of the parameter file
    @param	type	Receives the type of the parameter file:
			<br>GFPARM_PARAMETER normal parameter file
			<br>GFPARM_TEMPLATE template containing min and max values
    @return	handle on the parameters
	        <br>NULL on error.
    @warning	When the file does not exist, the (*name) parameter is set to NULL.
 */
void *
GfParmReadFile(const char *file, int mode)
{
    FILE	*in;
    char	buf[BUFSIZ];
    XML_Parser	parser;
    int		done;
    struct stat st;
    int		toload;
    int		fileExists;

    if (stat(file, &st)) {
	if (!(mode & GFPARM_RMODE_CREAT)) {
	    return NULL;
	}
	fileExists = 0;
    } else {
	fileExists = 1;
    }

    /* Verify if the file has already been read */
    CurParm = gfCheckParmWithFile(file, mode, &toload);
    if (toload == 0) {
	return (void*)CurParm;
    }
    
    /* CurParm contains a free tParm slot */
    CurParm->file = strdup(file);
    CurParm->mode = 0;
    CurParm->n.type = PARM_NODE_ROOT;
    CurParm->n.parent = (tParmNode*)CurParm;

    if (!fileExists) {
	CurParm->mode = GFPARM_WRITABLE | GFPARM_MODIFIABLE;
	GfOut("GfReadParmFile: file %s not existing\n", file);
	TheCurNode = (tParmNode*)calloc(1, sizeof(tParmNode));
	CurParm->n.kids = TheCurNode;
	TheCurNode->type = PARM_NODE_PARM;
	TheCurNode->next = TheCurNode;
	TheCurNode->prev = TheCurNode;
	TheCurNode->parent = (tParmNode*)CurParm;
	return (void*)CurParm;
    }
    
    
    if ((in = fopen(file, "r")) == NULL) {
	perror(file);
	GfTrace1("GfReadParmFile: file %s has pb\n", file);
	GfParmReleaseHandle((void*)CurParm);
	return NULL;
    }
    
    parser = XML_ParserCreate((XML_Char*)NULL);
    XML_SetElementHandler(parser, startElement, endElement);
    XML_SetExternalEntityRefHandler(parser, externalEntityRefHandler);
    do {
	size_t len = fread(buf, 1, sizeof(buf), in);
	done = len < sizeof(buf);
	if (!XML_Parse(parser, buf, len, done)) {
	    GfTrace3("GfReadParmFile: %s -> %s at line %d\n",
		     file,
		     XML_ErrorString(XML_GetErrorCode(parser)),
		     XML_GetCurrentLineNumber(parser));
	    GfParmReleaseHandle((void*)CurParm);
	    fclose(in);
	    return NULL;
	}
    } while (!done);
    XML_ParserFree(parser);

    fclose(in);
    return (void*)CurParm;
}


/** Get the pararmeters name
    @ingroup	params
    @param	handle	Handle on the parameters
    @return	Name
*/
char *
GfParmGetName(void *handle)
{
    return ((tParm*)handle)->n.kids->name;
}


/** Write a parameter file.
    @ingroup	params
    @param	file	Filename of the parameter file (local to $BASE/runtime)
    @param	handle	Handle on the parameters
    @param	name	Name of the parameters
    @param	type	type of the parameter file
    @param	dtd	Filename of the dtd file
    @return	0	ok
    		<br>-1	failed
    @warning	The file is created if necessary	
    @see	GfParmReadFile
 */
#define FW(buf)	if(fwrite((const void*)buf,strlen(buf),1,out)!=1){perror(file);GfTrace("GfParmWriteFile: error\n");return -1;}
#define BLANK for(i = 0; i < indent*2; i++) blank[i] = ' '; blank[i] = 0;
int
GfParmWriteFile(const char *file, void* handle, char *name, int type, const char *dtd)
{
    static	char *typeStr[2] = {GFPARM_PARAM_STR, GFPARM_TEMPL_STR};
    char	buf[BUFMAX];
    char	blank[BUFMAX];
    int		indent, i;
    char	*s;
    FILE	*out;
    tParmWithin	*curWithin;
    tParmSect	*curSect;
    tParmNode	*curNode;

    CurParm = (tParm*)handle;
    if (CurParm == NULL) return -1;

#ifndef DEBUG
    if ((CurParm->mode & GFPARM_WRITABLE) == 0) {
	GfTrace1("GfParmWriteFile: file %s is not allowed to be rewrited\n", file);
	/* return -1; */
    }
#endif

    if ((out = fopen(file, "w")) == NULL) {
	perror(file);
	GfTrace1("GfParmWriteFile: file %s has pb\n", file);
	return -1;
    }

    if (CurParm->file) free(CurParm->file);
    CurParm->file = strdup(file);
    
    sprintf(buf, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    FW(buf);
    sprintf(buf, "\n<!DOCTYPE params SYSTEM \"%s\">\n", dtd);
    FW(buf);
    
    indent = 1;
    if (CurParm->n.kids->name) free(CurParm->n.kids->name);
    CurParm->n.kids->name = strdup(name);
    CurParm->type = type;

    curNode = CurParm->n.kids;

    do {
	switch (curNode->type) {
	case PARM_NODE_PARM:
	    sprintf(buf, "\n<params name=\"%s\" type=\"%s\" mode=\"mw\">\n", name, typeStr[type]);
	    FW(buf);
	    break;
		
	case PARM_NODE_SECT:
	    curSect = (tParmSect*)curNode;
	    BLANK;
	    sprintf(buf, "\n%s<section name=\"%s\">\n", blank, curSect->n.name);
	    FW(buf);
	    break;

	case PARM_NODE_KEY:
	    tParmKey *curkey = (tParmKey*)curNode;
	    BLANK;
	    s = buf;
	    if (curkey->type == P_NUM) {
		s += sprintf(s, "%s<attnum name=\"%s\" ", blank, curkey->n.name);
		if (type == GFPARM_TEMPLATE) {
		    s += sprintf(s, "min=\"%f\" max=\"%f\" ", curkey->min, curkey->max);
		} 
		sprintf(s, "val=\"%f\"></attnum>\n", curkey->valnum);
	    } else {
		s += sprintf(s, "%s<attstr name=\"%s\" ", blank, curkey->n.name);
		if ((type == GFPARM_TEMPLATE) && (curkey->withins)) {
		    s += sprintf(s, "in=\"");
		    curWithin = curkey->withins;
		    do {
			curWithin = curWithin->next;
			s += sprintf(s, "%s,", curWithin->val);
		    } while (curWithin != curkey->withins);
		    s--;
		    s += sprintf(s, "\" ");
		} 
		sprintf(s, "val=\"%s\"></attstr>\n", curkey->valstr);
	    }
	    FW(buf);
	    break;
	}


	if (curNode->kids != NULL) {
	    curNode = curNode->kids;
	    indent++;
	} else {
	    /* No kids, this should be an attr... so it is self terminated */
	    curNode = curNode->next;
	    while ((curNode->type != PARM_NODE_PARM) && (curNode == curNode->parent->kids)) {
		/* end of kids list go back to the parent and write the end tag */
		curNode = curNode->parent;
		indent--;
		switch (curNode->type) {
		case PARM_NODE_PARM:
		    sprintf(buf, "\n</params>\n");
		    FW(buf);
		    break;
		case PARM_NODE_SECT:
		    BLANK;
		    sprintf(buf, "%s</section>\n", blank);
		    FW(buf);	    
		    break;
		}
		curNode = curNode->next;
	    }
	}

    } while (curNode->type != PARM_NODE_PARM);
    fclose(out);
    return 0;
}



/*
 * Search the node with the path...
 * the path is / separated.
 */
static tParmNode *
gfParmGetNode(tParm *curParm, char *path)
{
    tParmNode	*curNode = NULL;
    tParmNode	*kidNode = NULL;
    char	*wpath;
    char	*s1, *s2;
    int		found;

    if (curParm == NULL) {
	return NULL;
    }
    if ((path == NULL) || (strlen(path) == 0)) {
	return curParm->n.kids;
    }
    curNode = curParm->n.kids;
    wpath = strdup(path);
    s1 = wpath;
    while (*s1 == '/' && *s1 != 0) {
	s1++;
    }
    if (*s1 != 0) {
	do {
	    s2 = strchr(s1, '/');
	    if (s2 != NULL) {
		*s2 = 0;
	    }
	    kidNode = curNode->kids;
	    if (kidNode == NULL) { /* not found */
		free(wpath);
		return NULL;
	    }
	    found = 0;
	    do {
		if (strcmp(s1, kidNode->name)) {
		    kidNode = kidNode->next;
		} else {
		    found = 1;
		    break;
		}
	    } while (kidNode != curNode->kids);
	    if (!found) { /* not found */
		free(wpath);
		return NULL;
	    }
	    curNode = kidNode;
	    if (s2 != NULL) {
		/* search for the next level */
		s1 = s2 + 1;
		while (*s1 == '/' && *s1 != 0) {
		    s1++;
		}
		if (*s1 == 0) {
		    s2 = s1 = NULL;
		}
	    }
	} while (s2 != NULL);
    }

    free(wpath);
    return curNode;
}


/** Count the number of elements of a list.
    @ingroup	params
    @param	handle	handle of parameters
    @param	path	path of list
    @return	element count
 */
int
GfParmGetEltNb(void *handle, char *path)
{
    tParmNode	*curNode;
    tParmNode	*kidNode;
    int		count;

    curNode = gfParmGetNode((tParm *)handle, path);
    if ((curNode == NULL) || (curNode->kids == NULL)) {
	return 0;
    }

    kidNode = curNode->kids;
    count = 0;
    do {
	kidNode = kidNode->next;
	count++;
    } while (kidNode != curNode->kids);

    return count;
}

/** Seek the first element of a list.
    @ingroup	params
    @param	handle	handle of parameters
    @param	path	list path
    @return	0 Ok
    		<br>-1 Failed
    @see	GfParmListSeekNext
    @see	GfParmListGetCurEltName
 */
int
GfParmListSeekFirst(void *handle, char *path)
{
    tParmNode	*curNode;

    curNode = gfParmGetNode((tParm *)handle, path);
    if ((curNode == NULL) || (curNode->kids == NULL)) {
	return -1;
    }
    ((tParmSect*)curNode)->current = curNode->kids;
    return 0;
}

static void
gfRemoveNode(tParmNode *node)
{
    tParm	*curParm;

    if (node == NULL) {
	return;
    }
    if (node->next == node) {
	node->parent->kids = NULL;
    } else {
	node->next->prev = node->prev;
	node->prev->next = node->next;
	if (node->parent && (node->parent->kids == node)) {
	    node->parent->kids = node->next;
	}
    }
    
    switch (node->type) {
    case PARM_NODE_ROOT:
	curParm = (tParm*)node;
	if (curParm->file) free(curParm->file);
	curParm->file = NULL;
	free(node);
	break;	
    case PARM_NODE_PARM:
    case PARM_NODE_SECT:
	free(node->name);
	free(node);
	break;
    case PARM_NODE_KEY:
	tParmKey *curKey = (tParmKey*)node;

	free(node->name);
	if (curKey->valstr != NULL) free(curKey->valstr);
	if (curKey->withins != NULL) {
	    ParmWithin *curWithin = curKey->withins;
	    ParmWithin *nextWithin = curWithin->next;
	    do {
		curWithin = nextWithin;
		nextWithin = curWithin->next;
		free(curWithin->val);
		free(curWithin);
	    } while (curWithin != curKey->withins);
	}
	free(node);
	break;
    }
}


/*
 * Clean all the nodes
 */
static void
gfCleanNode(tParmNode *node)
{
    if (node == NULL) {
	return;
    }
    while (node->kids != NULL) {
	/* deep first */
	gfCleanNode(node->kids);
    }
    /* no more kids remove the node */
    gfRemoveNode(node);
}


/** Remove all the elements of a list.
    @ingroup	params
    @param	handle	handle of parameters
    @param	path	path of list
    @return	0 Ok
		<br>-1 Error
 */
int
GfParmListClean(void *handle, char *path)
{
    tParmNode	*curNode;

    curNode = gfParmGetNode((tParm *)handle, path);
    if (curNode == NULL) {
	return -1;
    }
    
    gfCleanNode(curNode->kids);
    curNode->kids = NULL;
    ((tParmSect*)curNode)->current = NULL;

    return 0;
}

/** Go to the next element in the current list.
    @param	handle	handle of parameters
    @param	path	path of list
    @return	0 Ok
    		<br>1 End of list reached
    		<br>-1 Failed
    @see	GfParmListSeekFirst	
    @see	GfParmListGetCurEltName
 */
int
GfParmListSeekNext(void *handle, char *path)
{
    tParmNode	*curNode;
    tParmNode	*curElt;

    curNode = gfParmGetNode((tParm *)handle, path);
    if ((curNode == NULL) || (curNode->kids == NULL)) {
	return -1;
    }
    
    curElt = ((tParmSect*)curNode)->current->next;
    ((tParmSect*)curNode)->current = curElt;
    if (curElt == curNode->kids) {
	return 1;
    }
    
    return 0;
}

/** Get The current element name.
    @ingroup	params
    @param	handle	handle of parameters
    @param	path	path of list
    @return	Name of the current element in the list
		<br>NULL if failed
    @see	GfParmListSeekFirst	
    @see	GfParmListSeekNext
 */
char *
GfParmListGetCurEltName(void *handle, char *path)
{
    tParmNode	*curNode;

    curNode = gfParmGetNode((tParm *)handle, path);
    if ((curNode == NULL) || (((tParmSect*)curNode)->current == NULL)) {
	return NULL;
    }
    
    return strdup(((tParmSect*)curNode)->current->name);
}

static tParmKey *
GetKey(void *handle, char *path, char *key)
{
    char	Buf[BUFMAX];
    tParmNode	*curNode;

    sprintf(Buf, "%s/%s", path, key);
    curNode = gfParmGetNode((tParm *)handle, Buf);
    return (tParmKey*)curNode;
}


/*
 * Create the path under the node
 */
static tParmNode *
gfCreatePath(tParmNode *curNode, char *path)
{
    char	*s1, *s2;
    char	*wpath;
    int		found;
    tParmSect	*cursect;
    tParmNode	*kidNode;
    
    if ((path == NULL) || (strlen(path) == 0)) {
	return curNode;
    }

    wpath = strdup(path);
    s1 = wpath;
    while (*s1 == '/' && *s1 != 0) {
	s1++;
    }
    if (*s1 != 0) {
	do {
	    s2 = strchr(s1, '/');
	    if (s2 != NULL) {
		*s2 = 0;
	    }
	    kidNode = curNode->kids;
	    if (kidNode == NULL) { /* not found */
		if (s2 != NULL) {
		    *s2 = '/'; /* back to the full remaining path */
		}
		break;
	    }
	    found = 0;
	    do {
		if (strcmp(s1, kidNode->name)) {
		    kidNode = kidNode->next;
		} else {
		    found = 1;
		    break;
		}
	    } while (kidNode != curNode->kids);
	    if (!found) { /* not found */
		if (s2 != NULL) {
		    *s2 = '/'; /* back to the full remaining path */
		}
		break;
	    }
	    curNode = kidNode;
	    if (s2 != NULL) {
		/* search for the next level */
		s1 = s2 + 1;
		while (*s1 == '/' && *s1 != 0) {
		    s1++;
		}
		if (*s1 == 0) {
		    s2 = s1 = NULL;
		}
	    } else {
		s1 = NULL;
	    }
	} while (s2 != NULL);
    }
    
    if (s1 != NULL) {
	/* path not complete create */
	while (*s1 == '/' && *s1 != 0) {
	    s1++;
	}
	if (*s1 != 0) {
	    do {
		s2 = strchr(s1, '/');
		if (s2 != NULL) {
		    *s2 = 0;
		}

		cursect = (tParmSect*)calloc(1, sizeof(tParmSect));
		cursect->n.type = PARM_NODE_SECT;
		gfParmAddKid(curNode, (tParmNode*)cursect);
		curNode = (tParmNode*)cursect;
		curNode->name = strdup(s1);

		if (s2 != NULL) {
		    /* search for the next level */
		    s1 = s2 + 1;
		    while (*s1 == '/' && *s1 != 0) {
			s1++;
		    }
		    if (*s1 == 0) {
			s2 = s1 = NULL;
		    }
		}
	    } while (s2 != NULL);
	}
    }
    free(wpath);
    return curNode;
}

static tParmNode *
gfParmGetCurPath(void *handle, char *path)
{
    tParmNode	*curNode;

    curNode = gfParmGetNode((tParm *)handle, path);
    if ((curNode == NULL) || (curNode->kids == NULL)) {
	return NULL;
    }
    
    return ((tParmSect*)curNode)->current;

}

static tParmKey *
gfGetCurKey(void *handle, char *path, char *key)
{
    tParmNode	*curNode;
    tParmNode	*kidNode;
    
    curNode = gfParmGetNode((tParm *)handle, path);
    if ((curNode == NULL) || (curNode->kids == NULL)) {
	return NULL;
    }
    curNode = ((tParmSect*)curNode)->current;
    if (curNode == NULL) {
	return NULL;
    }
    kidNode = curNode->kids;
    if (kidNode == NULL) { /* not found */
	return NULL;
    }
    do {
	if (strcmp(key, kidNode->name)) {
	    kidNode = kidNode->next;
	} else {
	    return (tParmKey *)kidNode;
	}
    } while (kidNode != curNode->kids);

    return NULL;
}


/** Get a string parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	default	default string	
    @return	parameter value
    @warning	the return value is allocated by the function the caller must free it.
*/
char *
GfParmGetStr(void *handle, char *path, char *key, char *deflt)
{
    char	Buf[BUFMAX];
    tParmKey	*curKey;
    tParmNode	*curNode;

    sprintf(Buf, "%s/%s", path, key);
    curNode = gfParmGetNode((tParm *)handle, Buf);
    curKey = (tParmKey*)curNode;
    
    if ((curNode == NULL)  || (curNode->type != PARM_NODE_KEY) ||  (curKey->type != P_STR)) {
	/* return strdup(deflt); */
	return deflt;
    }	

    /* key found, return value */
    /* return strdup(curKey->valstr); */
    return curKey->valstr;
}


/** Get a string parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	default	default string	
    @return	parameter value
    @warning	the return value is allocated by the function the caller must free it.
    @see	GfParmListSeekNext
*/
char *
GfParmGetCurStr(void *handle, char *path, char *key, char *deflt)
{
    tParmKey	*curKey;

    curKey = gfGetCurKey(handle, path, key);

    if ((curKey == NULL)  || (curKey->n.type != PARM_NODE_KEY) ||  (curKey->type != P_STR)) {
	/* return strdup(deflt); */
	return deflt;
    }	

    /* key found, return value */
    /* return strdup(curKey->valstr); */
    return curKey->valstr;
}


/** Get a numerical parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	unit	unit to convert the result to (NULL if SI wanted)	
    @param	default	default string	
    @return	parameter value
 */
tdble
GfParmGetNum(void *handle, char *path, char *key, char *unit, tdble deflt)
{
    char	Buf[BUFMAX];
    tParmKey	*curKey;
    tParmNode	*curNode;

    sprintf(Buf, "%s/%s", path, key);
    curNode = gfParmGetNode((tParm *)handle, Buf);
    curKey = (tParmKey*)curNode;
    
    if ((curNode == NULL)  || (curNode->type != PARM_NODE_KEY) ||  (curKey->type != P_NUM)) {
	return deflt;
    }	

    /* key found, return value */
    return GfParmSI2Unit(unit, curKey->valnum);
}

/** Get a numerical parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	unit	unit to convert the result to (NULL if SI wanted)	
    @param	default	default string	
    @return	parameter value
 */
tdble
GfParmGetCurNum(void *handle, char *path, char *key, char *unit, tdble deflt)
{
    tParmKey	*curKey;

    curKey = gfGetCurKey(handle, path, key);

    if ((curKey == NULL)  || (curKey->n.type != PARM_NODE_KEY) ||  (curKey->type != P_NUM)) {
	return deflt;
    }	

    /* key found, return value */
    return GfParmSI2Unit(unit, curKey->valnum);
}


/** Set a string parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	val	value	
    @return	0	ok
    		<br>-1	error
    @warning	The key is created is necessary	
 */
int
GfParmSetStr(void *handle, char *path, char *key, char *val)
{
    tParmNode	*curNode;
    tParmNode	*kidNode;
    tParm	*curParm;
    tParmKey	*curkey;
    int		found;
    
    curParm = (tParm*)handle;

    if (handle == NULL) {
	return -1;
    }

#ifdef DEBUG
    if ((curParm->mode & GFPARM_MODIFIABLE) == 0) {
	GfTrace1("GfParmWriteFile: file %s is not allowed to be modified\n", curParm->file);
	/* return -1; */
    }
#endif

    if ((path == NULL) || (strlen(path) == 0) || (key == NULL) || (strlen(key) == 0)) {
	return -1;
    }
    curNode = curParm->n.kids;
    curNode = gfCreatePath(curNode, path);
    kidNode = curNode->kids;
    found = 0;
    if (kidNode != NULL) {
	do {
	    if (strcmp(key, kidNode->name)) {
		kidNode = kidNode->next;
	    } else {
		curNode = kidNode;
		found = 1;
		break;
	    }
	} while (kidNode != curNode->kids);
    }
    if (!found) {
	/* Create Key */
	curkey = (tParmKey*)calloc(1, sizeof(tParmKey));
	curkey->n.name = strdup(key);
	curkey->n.type = PARM_NODE_KEY;
	curkey->type = P_STR;
	gfParmAddKid(curNode, (tParmNode*)curkey);
	if (val) curkey->valstr = strdup(val);
    } else {
	curkey = (tParmKey*)curNode;
	if (curkey->valstr) free(curkey->valstr);
	if (val) curkey->valstr = strdup(val);
    }
    return 0;
}

/** Set a string parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	val	value	
    @return	0	ok
    		<br>-1	error
    @warning	The key is created is necessary	
 */
int
GfParmSetCurStr(void *handle, char *path, char *key, char *val)
{
    tParmNode	*curNode;
    tParmNode	*kidNode;
    tParm	*curParm;
    tParmKey	*curkey;
    int		found;
    
    curParm = (tParm*)handle;

    if (handle == NULL) {
	return -1;
    }

#ifdef DEBUG
    if ((curParm->mode & GFPARM_MODIFIABLE) == 0) {
	GfTrace1("GfParmWriteFile: file %s is not allowed to be modified\n", curParm->file);
	/* return -1; */
    }
#endif

    if ((path == NULL) || (strlen(path) == 0) || (key == NULL) || (strlen(key) == 0)) {
	return -1;
    }
    curNode = gfParmGetCurPath(handle, path);
    if (curNode == NULL) {
	return -1;
    }
    kidNode = curNode->kids;
    found = 0;
    if (kidNode != NULL) {
	do {
	    if (strcmp(key, kidNode->name)) {
		kidNode = kidNode->next;
	    } else {
		curNode = kidNode;
		found = 1;
		break;
	    }
	} while (kidNode != curNode->kids);
    }
    if (!found) {
	/* Create Key */
	curkey = (tParmKey*)calloc(1, sizeof(tParmKey));
	curkey->n.name = strdup(key);
	curkey->n.type = PARM_NODE_KEY;
	curkey->type = P_STR;
	gfParmAddKid(curNode, (tParmNode*)curkey);
	if (val) curkey->valstr = strdup(val);
    } else {
	curkey = (tParmKey*)curNode;
	if (curkey->valstr) free(curkey->valstr);
	if (val) curkey->valstr = strdup(val);
    }
    return 0;
}


/** Set a numerical parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	unit	unit to convert the result to (NULL if SI wanted)	
    @param	val	value to set	
    @return	0	ok
    		<br>-1	error
    @warning	The key is created is necessary
 */
int
GfParmSetNum(void *handle, char *path, char *key, char *unit, tdble val)
{
    tParmNode	*curNode;
    tParmNode	*kidNode;
    tParm	*curParm;
    tParmKey	*curKey;
    int		found;
    
    curParm = (tParm*)handle;

    if (handle == NULL) {
	return -1;
    }

#ifdef DEBUG
    if ((curParm->mode & GFPARM_MODIFIABLE) == 0) {
	GfTrace1("GfParmWriteFile: file %s is not allowed to be modified\n", curParm->file);
	/* return -1; */
    }
#endif

    if ((path == NULL) || (strlen(path) == 0) || (key == NULL) || (strlen(key) == 0)) {
	return -1;
    }
    curNode = curParm->n.kids;
    curNode = gfCreatePath(curNode, path);
    kidNode = curNode->kids;
    found = 0;
    if (kidNode != NULL) {
	do {
	    if (strcmp(key, kidNode->name)) {
		kidNode = kidNode->next;
	    } else {
		curNode = kidNode;
		found = 1;
		break;
	    }
	} while (kidNode != curNode->kids);
    }
    if (!found) {
	/* Create Key */
	curKey = (tParmKey*)calloc(1, sizeof(tParmKey));
	curKey->n.name = strdup(key);
	curKey->n.type = PARM_NODE_KEY;
	gfParmAddKid(curNode, (tParmNode*)curKey);	
	curKey->type = P_NUM;
    } else {
	/* key found, modify it */
	curKey = (tParmKey*)curNode;
    }
    val = GfParmUnit2SI(unit, val);
    curKey->valnum = val;
    curKey->min = val;
    curKey->max = val;
    return 0;
}

/** Set a numerical parameter in a config file.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of param
    @param	key	key name	
    @param	unit	unit to convert the result to (NULL if SI wanted)	
    @param	val	value to set	
    @return	0	ok
    		<br>-1	error
    @warning	The key is created is necessary
 */
int
GfParmSetCurNum(void *handle, char *path, char *key, char *unit, tdble val)
{
    tParmNode	*curNode;
    tParmNode	*kidNode;
    tParm	*curParm;
    tParmKey	*curKey;
    int		found;
    
    curParm = (tParm*)handle;

    if (handle == NULL) {
	return -1;
    }

#ifdef DEBUG
    if ((curParm->mode & GFPARM_MODIFIABLE) == 0) {
	GfTrace1("GfParmWriteFile: file %s is not allowed to be modified\n", curParm->file);
	/* return -1; */
    }
#endif

    if ((path == NULL) || (strlen(path) == 0) || (key == NULL) || (strlen(key) == 0)) {
	return -1;
    }
    curNode = gfParmGetCurPath(handle, path);
    if (curNode == NULL) {
	return -1;
    }
    kidNode = curNode->kids;
    found = 0;
    if (kidNode != NULL) {
	do {
	    if (strcmp(key, kidNode->name)) {
		kidNode = kidNode->next;
	    } else {
		curNode = kidNode;
		found = 1;
		break;
	    }
	} while (kidNode != curNode->kids);
    }
    if (!found) {
	/* Create Key */
	curKey = (tParmKey*)calloc(1, sizeof(tParmKey));
	curKey->n.name = strdup(key);
	curKey->n.type = PARM_NODE_KEY;
	gfParmAddKid(curNode, (tParmNode*)curKey);	
	curKey->type = P_NUM;
    } else {
	/* key found, modify it */
	curKey = (tParmKey*)curNode;
    }
    val = GfParmUnit2SI(unit, val);
    curKey->valnum = val;
    curKey->min = val;
    curKey->max = val;
    return 0;
}

/** Free all Parameters for a handle.
    @ingroup	params
    @param	handle	handle of parameters
    @return	<tt>0 ... </tt>Ok
		<br><tt>-1 .. </tt>Error
    @warning	The handle is kept existing, a WriteParmFile will clean the file.
    @see	GfParmWriteFile
 */
int
GfParmClean(void *handle)
{
    tParm	*curParm;
    tParmNode	*node;
    
    if (handle == NULL) {
	return 0;
    }
    curParm = (tParm*)handle;
    if (curParm->file) free(curParm->file);
    curParm->file = NULL;
    node = curParm->n.kids;
    while (node->kids != NULL) {
	/* deep first */
	gfCleanNode(node->kids);
    }

    return 0;
    
}


/** Release the parameters handle without removing data from the file.
    @ingroup	params
    @param	handle handle on the parameters
    @return	0 Ok
		<br>-1 Error
    @warning	The handle must not be used anymore.
    @see	GfParmClean
 */
int
GfParmReleaseHandle(void *handle)
{
    tParm	*rmParm = (tParm*)handle;

    if (handle == NULL) {
	return 0;
    }
    
    rmParm->refcount--;

    if (rmParm->refcount > 0) {
	return 0;
    }
    
    GfParmClean(handle);
    
    /* Remove the handle in the list */
    if (TheParms != NULL) {
	if (rmParm->n.next == (tParmNode*)rmParm) {
	    /* only one element */
	    TheParms = NULL;
	} else if (TheParms == rmParm) {
	    TheParms = (tParm*)rmParm->n.next;
	}
	//gfRemoveNode(rmParm->n.kids);
	gfRemoveNode((tParmNode*)rmParm);
    }
    return 0;
}

static void
evalUnit(char *unit, tdble *dest, int flg)
{
    tdble coeff = 1.0;
    
    if (strcmp(unit, "m") == 0) return;
    if (strcmp(unit, "kg") == 0) return;
    if (strcmp(unit, "s") == 0) return;
    if (strcmp(unit, "rad") == 0) return;
    if (strcmp(unit, "Pa") == 0) return;

    if ((strcmp(unit, "feet") == 0) || (strcmp(unit, "ft") == 0)) {
	coeff = 0.304801; /* m */
    } else if (strcmp(unit, "deg") == 0) {
	coeff = M_PI/180.0; /* rad */
    } else if ((strcmp(unit, "h") == 0) || (strcmp(unit, "hour") == 0) || (strcmp(unit, "hours") == 0)) {
	coeff = 3600.0; /* s */
    } else if ((strcmp(unit, "day") == 0) || (strcmp(unit, "days") == 0)) {
	coeff = 24*3600.0; /* s */
    } else if (strcmp(unit, "km") == 0) {
	coeff = 1000.0; /* m */
    } else if (strcmp(unit, "mm") == 0) {
	coeff = 0.001; /* m */
    } else if (strcmp(unit, "cm") == 0) {
	coeff = 0.01; /* m */
    } else if ((strcmp(unit, "in") == 0) || (strcmp(unit, "inch") == 0) || (strcmp(unit, "inches") == 0)) {
	coeff = 0.0254; /* m */
    } else if ((strcmp(unit, "lbs") == 0)  || (strcmp(unit, "lb") == 0)) {
	coeff = 0.45359237; /* kg */
    } else if ((strcmp(unit, "slug") == 0) || (strcmp(unit, "slugs") == 0)) {
	coeff = 14.59484546; /* kg */
    } else if (strcmp(unit, "kPa") == 0) {
	coeff = 1000.0; /* Pa */
    } else if (strcmp(unit, "MPa") == 0) {
	coeff = 1000000.0; /* Pa */
    } else if ((strcmp(unit, "PSI") == 0) || (strcmp(unit, "psi") == 0)){
	coeff = 6894.76; /* Pa */
    } else if ((strcmp(unit, "rpm") == 0) || (strcmp(unit, "RPM") == 0)) {
	coeff = 0.104719755; /* rad/s */
    } else if ((strcmp(unit, "percent") == 0) || (strcmp(unit, "%") == 0)) {
	coeff = 0.01;
    }

    if (flg) {
	*dest /= coeff;
    } else {
	*dest *= coeff;
    }
    
    return;
}

/** Convert a value in "units" into SI.
    @ingroup	params
    @param	unit	unit name
    @param	val	value in units
    @return	the value in corresponding SI unit
    @warning	The supported units are:
    			<br><dl><dd><b>feet</b> or <b>ft</b>  converted to <b>m</b>
			<dd><b>inches</b> or <b>in</b> converted to <b>m</b>
			<dd><b>lbs</b> converted to <b>kg</b>
			<dd><b>slug</b> or <b>slugs</b> converted to <b>kg</b>
			<dd><b>h</b> or <b>hours</b> converted to <b>s</b>
			<dd><b>day</b> or <b>days</b> converted to <b>s</b>
			<dd><b>km</b> converted to <b>m</b>
			<dd><b>cm</b> converted to <b>m</b>
			<dd><b>mm</b> converted to <b>m</b>
			<dd><b>kPa</b> converted to <b>Pa</b>
			<dd><b>deg</b> converted to <b>rad</b>
			<dd><b>rpm</b> or <b>RPM</b> converted to <b>rad/s</b>
			<dd><b>percent</b> or <b>%</b> divided by <b>100</b></dl>
    @see	GfParmSI2Unit
 */
tdble
GfParmUnit2SI(char *unit, tdble val)
{
    char buf[256];
    int  idx;
    char *s;
    int  inv;
    tdble dest = val;
    
    if ((unit == NULL) || (strlen(unit) == 0)) return dest;

    s = unit;
    buf[0] = 0;
    inv = 0;
    idx = 0;
    
    while (*s != 0) {
	switch (*s) {
	case '.':
	    evalUnit(buf, &dest, inv);
	    buf[0] = 0;
	    idx = 0;
	    break;
	case '/':
	    evalUnit(buf, &dest, inv);
	    buf[0] = 0;
	    idx = 0;
	    inv = 1;
	    break;
	case '2':
	    evalUnit(buf, &dest, inv);
	    evalUnit(buf, &dest, inv);
	    buf[0] = 0;
	    idx = 0;
	    break;	    
	default:
	    buf[idx++] = *s;
	    buf[idx] = 0;
	    break;
	}
	s++;
    }
    evalUnit(buf, &dest, inv);
    return dest;
}

/** Convert a value in SI to "units".
    @ingroup	params
    @param	unit	unit name to convert to
    @param	val	value in SI units to be converted to units
    @return	converted value to units
    @see	GfParmUnit2SI
 */
tdble
GfParmSI2Unit(char *unit, tdble val)
{
    char buf[256];
    int  idx;
    char *s;
    int  inv;
    tdble dest = val;
    
    if ((unit == NULL) || (strlen(unit) == 0)) return dest;

    s = unit;
    buf[0] = 0;
    inv = 1;
    idx = 0;
    
    while (*s != 0) {
	switch (*s) {
	case '.':
	    evalUnit(buf, &dest, inv);
	    buf[0] = 0;
	    idx = 0;
	    break;
	case '/':
	    evalUnit(buf, &dest, inv);
	    buf[0] = 0;
	    idx = 0;
	    inv = 0;
	    break;
	case '2':
	    evalUnit(buf, &dest, inv);
	    evalUnit(buf, &dest, inv);
	    buf[0] = 0;
	    idx = 0;
	    break;	    
	default:
	    buf[idx++] = *s;
	    buf[idx] = 0;
	    break;
	}
	s++;
    }
    evalUnit(buf, &dest, inv);
    return dest;
}


/*
 * Function
 *	CheckParm
 *
 * Description
 *	
 *
 * Parameters
 *	
 *
 * Return
 *	0  - ok
 *	-1 - nok
 */
static int
CheckParm(void *handle, char *path, char *key, tParmKey *testKey)
{
    char	Buf[BUFMAX];
    tParmKey	*curKey;
    tParmNode	*curNode;
    tParmWithin	*curWithin;

    sprintf(Buf, "%s/%s", path, key);
    curNode = gfParmGetNode((tParm *)handle, Buf);
    curKey = (tParmKey*)curNode;
    
    if ((curNode == NULL)  || (curNode->type != PARM_NODE_KEY)) {
	return 0;
    }	

    if (curKey->type == P_NUM) {
	if (testKey->valnum > curKey->max) { 
	    GfTrace2("bad path: %s  key: %s\n", path, curKey->n.name);
	    GfTrace3("min: %f  max: %f  value: %f\n", curKey->min, curKey->max, testKey->valnum);
	    testKey->valnum = curKey->max;
	    return 0;
	} else if (testKey->valnum < curKey->min) {
	    GfTrace2("bad path: %s  key: %s\n", path, curKey->n.name);
	    GfTrace3("min: %f  max: %f  value: %f\n", curKey->min, curKey->max, testKey->valnum);
	    testKey->valnum = curKey->min;
	    return 0;
	} else {
	    return 0;
	}
    }
    
    /* not a numerical value */
    if (curKey->withins != NULL) {
	curWithin = curKey->withins;
	do {
	    curWithin = curWithin->next;
	    if (strcmp(testKey->valstr, curWithin->val) == 0) {
		return 0;
	    }
	} while (curWithin != curKey->withins);
	GfTrace3("bad key: %s/%s = %s\n", path, curKey->n.name, testKey->valstr);
	return -1;
    }
   
    /* no min/max/unit nor list provided, just check the value string */
    if (strcmp(curKey->valstr, testKey->valstr) == 0) {
	return 0;
    }
    GfTrace3("bad key: %s/%s = %s\n", path, curKey->n.name, testKey->valstr);
    return -1;
}

/** Check a parameter set against another.
    @ingroup	params
    @param	ref	Contains the min and max values (reference)
    @param	tgt	Contains the parameters to check.
    @return	0 Match
		<br>-1 Values are out of bounds
    @warning	<b>ref</b> must be a template file (type: GFPARM_TEMPLATE)
    @warning	Only the parameters present in tgt and in ref are tested.
    @see	GfParmMergeHandles
 */
int
GfParmCheckHandle(void *ref, void *tgt)
{
    char	Buf[BUFMAX];
    tParm	*parm = (tParm*)tgt;
    tParm	*parmref = (tParm*)ref;
    tParmNode	*curNode;
    char	*s1;

    if ((ref == NULL) || (tgt == NULL)) {
	GfTrace("Null parameters cannot fit\n");
	return -1;
    }
    
    if (parmref->type != GFPARM_TEMPLATE) {
	/* only compare with a template file */
	GfTrace("The file is not a template file\n");
	return -1;
    }
    
    s1 = Buf;
    curNode = parm->n.kids;
    do {
	if (curNode->kids != NULL) {
	    curNode = curNode->kids;
	    s1 += sprintf(s1, "/%s", curNode->name);
	} else {
	    s1 = strrchr(Buf, '/');
	    if (s1 == NULL) {
		break;
	    }
	    *s1 = 0;
	    /* No kids, this should be an attr... so it is self terminated */
	    if (CheckParm(parmref, Buf, s1+1, (tParmKey*)curNode)) {
		return -1;
	    }
	    curNode = curNode->next;
	    s1 += sprintf(s1, "/%s", curNode->name);
	    while ((curNode->type != PARM_NODE_PARM) && (curNode == curNode->parent->kids)) {
		/* end of kids list go back to the parent and write the end tag */
		s1 = strrchr(Buf, '/');
		*s1 = 0;
		curNode = curNode->parent;
		s1 = strrchr(Buf, '/');
		if (s1) *s1 = 0;
		curNode = curNode->next;
		if (s1) s1 += sprintf(s1, "/%s", curNode->name);
	    }
	}
    } while (curNode->type != PARM_NODE_PARM);


    return 0;
}


static void
mergekeys(tParmKey *newKey,
	  tParmKey *refKey,
	  tParmKey *tgtKey)
{
    tParmWithin	*curWithin;
    tParmWithin	*refWithin;
    tParmWithin	*newWithin;
    int		found;

    if ((tgtKey == NULL) || (refKey == NULL)) {
	if (tgtKey == NULL) {
	    tgtKey = refKey;
	}
	/* just copy */
	newKey->n.name = strdup(tgtKey->n.name);
	newKey->type = tgtKey->type;
	if (tgtKey->type == P_NUM) {
	    newKey->valnum = tgtKey->valnum;
	    newKey->min    = tgtKey->min;
	    newKey->max    = tgtKey->max;
	} else {
	    newKey->valstr = strdup(tgtKey->valstr);
	    if (tgtKey->withins != NULL) {
		curWithin = tgtKey->withins;
		do {
		    curWithin = curWithin->next;
		    newWithin = (tParmWithin*)calloc(1, sizeof(tParmWithin));
		    newWithin->val = strdup(curWithin->val);
		    if (newKey->withins == NULL) {
			newWithin->next = newWithin;
			newKey->withins = newWithin;
		    } else {
			newWithin->next = newKey->withins->next;
			newKey->withins->next = newWithin;
			newKey->withins = newWithin;
		    }
		} while (curWithin != tgtKey->withins);
	    }
	}
	return;
    }
    
    /* merge now, we assume that GfCheckHandles was called before */
    /* so the target value is a subset of the reference */
    if (refKey->type == P_NUM) {
	newKey->valnum = tgtKey->valnum;
	newKey->min    = MAX(tgtKey->min, refKey->min);
	newKey->max    = MIN(tgtKey->max, refKey->max);
	newKey->type   = P_NUM;
    } else {
	newKey->type   = P_STR;
	newKey->valstr = strdup(tgtKey->valstr);
	if ((tgtKey->withins != NULL) && (refKey->withins != NULL)) {
	    curWithin = tgtKey->withins;
	    do {
		curWithin = curWithin->next;
		found = 0;
		refWithin = refKey->withins;
		do {
		    refWithin = refWithin->next;
		    if (strcmp(curWithin->val, refWithin->val) == 0) {
			found = 1;
			break;
		    }
		} while (refWithin != refKey->withins);
		if (found) {
		    newWithin = (tParmWithin*)calloc(1, sizeof(tParmWithin));
		    newWithin->val = strdup(curWithin->val);
		    if (newKey->withins == NULL) {
			newWithin->next = newWithin;
			newKey->withins = newWithin;
		    } else {
			newWithin->next = newKey->withins->next;
			newKey->withins->next = newWithin;
			newKey->withins = newWithin;
		    }
		}		
	    } while (curWithin != tgtKey->withins);
	}
    }
}

/** Merge two parameters sets into a new one.
    @ingroup	params
    @param	ref	reference handle
    @param	tgt	target handle for merge
    @param	mode	merge mode, can be any combination of:
		<br>GFPARM_MMODE_SRC Use ref and modify existing parameters with tgt
		<br>GFPARM_MMODE_DST Use tgt and verify ref parameters
		<br>GFPARM_MMODE_RELSRC Release ref after the merge
		<br>GFPARM_MMODE_RELDST Release tgt after the merge
    @return	The new handle containing the merge.
    @warning	No test is done, GfParmCheckHandle must be called before to verify thst the parameters are compatible.
    @see	GfParmCheckHandle
 */
void *
GfParmMergeHandles(void *ref, void *tgt, int mode)
{
    char	Buf[BUFMAX];
    tParm	*newCurParm;
    tParmNode	*curNode;
    char	*s1;

    tParm	*parmref = (tParm*)ref;
    tParm	*parmtgt = (tParm*)tgt;
    tParmKey	*curKey;


    char	buf[256];
    
    if ((ref == NULL) || (tgt == NULL)) {
	return NULL;
    }

    if (TheParms == NULL) {
	return NULL;
    }

    if (parmref->type != GFPARM_TEMPLATE) {
	return NULL;
    }

    newCurParm = (tParm*)calloc(1, sizeof(tParm));
    newCurParm->refcount = 1;
    newCurParm->file = strdup("Merged");
    newCurParm->n.type = PARM_NODE_ROOT;
    newCurParm->n.next = TheParms->n.next;
    newCurParm->n.prev = newCurParm->n.next->prev;
    newCurParm->n.next->prev = (tParmNode*)newCurParm;
    newCurParm->n.prev->next = (tParmNode*)newCurParm;
    TheParms = newCurParm;
    
    if (parmtgt->type == GFPARM_TEMPLATE) {
	newCurParm->type = GFPARM_TEMPLATE;
    } else {
	newCurParm->type = GFPARM_PARAMETER;
    }
    newCurParm->mode = parmtgt->mode;

    sprintf(buf, "%s-%s", parmtgt->n.kids->name, parmref->n.kids->name);
    newCurParm->n.name = strdup(buf);

    tParmNode *newNode = (tParmNode*)calloc(1, sizeof(tParmNode));
    newCurParm->n.kids = newNode;
    newNode->type = PARM_NODE_PARM;
    newNode->next = newNode;
    newNode->prev = newNode;
    newNode->parent = (tParmNode*)newCurParm;

    if (mode & GFPARM_MMODE_SRC) {
	curNode = parmref->n.kids;

	s1 = Buf;
	do {
	    if (curNode->kids != NULL) {
		curNode = curNode->kids;
		s1 += sprintf(s1, "/%s", curNode->name);
	    } else {
		/* No kids, this should be an attr */
		s1 = strrchr(Buf, '/');
		*s1 = 0;
		/* create the new path */
		newNode = gfCreatePath(newCurParm->n.kids, Buf);
		/* allocate an empty key */
		curKey = (tParmKey*)calloc(1, sizeof(tParmKey));
		curKey->n.type = PARM_NODE_KEY;
		curKey->n.name = strdup(s1+1);
		gfParmAddKid(newNode, (tParmNode*)curKey);
		/* merge keys */
		mergekeys(curKey, (tParmKey*)curNode, GetKey(tgt, Buf, curNode->name));
		/* Next node same level */
		curNode = curNode->next;
		s1 += sprintf(s1, "/%s", curNode->name);
		while ((curNode->type != PARM_NODE_PARM) && (curNode == curNode->parent->kids)) {
		    /* end of kids list go back to the parent */
		    s1 = strrchr(Buf, '/');
		    *s1 = 0;
		    curNode = curNode->parent;
		    s1 = strrchr(Buf, '/');
		    if (s1) *s1 = 0;
		    curNode = curNode->next;
		    if (s1) s1 += sprintf(s1, "/%s", curNode->name);
		}
	    }
	} while (curNode->type != PARM_NODE_PARM);
    }

    if (mode & GFPARM_MMODE_DST) {
	curNode = parmtgt->n.kids;
	s1 = Buf;
	if (curNode->kids != NULL) {
	    
	    do {
		if (curNode->kids != NULL) {
		    curNode = curNode->kids;
		    s1 += sprintf(s1, "/%s", curNode->name);
		} else {
		    /* No kids, this should be an attr */
		    newNode = gfParmGetNode(newCurParm, Buf);
		    s1 = strrchr(Buf, '/');
		    *s1 = 0;
		    if (newNode == NULL) {
			/* create the new path */
			newNode = gfCreatePath(newCurParm->n.kids, Buf);
			/* allocate an empty key */
			curKey = (tParmKey*)calloc(1, sizeof(tParmKey));
			curKey->n.type = PARM_NODE_KEY;
			curKey->n.name = strdup(s1+1);
			gfParmAddKid(newNode, (tParmNode*)curKey);
			/* merge keys */
			mergekeys(curKey, GetKey(ref, Buf, curNode->name), (tParmKey*)curNode);
		    }
		    /* Next node same level */
		    curNode = curNode->next;
		    s1 += sprintf(s1, "/%s", curNode->name);
		    while ((curNode->type != PARM_NODE_PARM) && (curNode == curNode->parent->kids)) {
			/* end of kids list go back to the parent */
			s1 = strrchr(Buf, '/');
			*s1 = 0;
			curNode = curNode->parent;
			s1 = strrchr(Buf, '/');
			if (s1) *s1 = 0;
			curNode = curNode->next;
			if (s1) s1 += sprintf(s1, "/%s", curNode->name);
		    }
		}
	    } while (curNode->type != PARM_NODE_PARM);
	}
    }


    if (mode & GFPARM_MMODE_RELSRC) {
	GfParmReleaseHandle(ref);
    }
    if (mode & GFPARM_MMODE_RELDST) {
	GfParmReleaseHandle(tgt);
    }
    
    return (void*)newCurParm;
}

/** Get the min and max of a numerical parameter.
    @ingroup	params
    @param	handle	handle of parameters	
    @param	path	path of the attribute
    @param	key	key name	
    @param	min	Receives the min value
    @param	max	Receives the max value
    @return	0 Ok
		<br>-1 Parameter not existing
 */
int
GfParmGetNumBoundaries(void *handle, char *path, char *key, tdble *min, tdble *max)
{
    tParmKey	*curKey;

    curKey = GetKey(handle, path, key);
    if ((curKey == NULL) || (curKey->type != P_NUM)) {
	return -1;
    }
    
    /* key found, return boundaries */
    *min = curKey->min;
    *max = curKey->max;

    return 0;
}

 
