/***************************************************************************

    file                 : params.h
    created              : Mon Jan 31 22:19:04 CET 2000
    copyright            : (C) 2000 by Eric Espie
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
 

#ifndef _PARAMS_H_
#define _PARAMS_H_


#define LINE_SZ		1024

#define PARAM_CREATE	0x01

#define P_NUM 0
#define P_STR 1

/** Parameter header structure */
typedef struct param
{
    char				*name;		/**< Name of the parameter  */
    char				*fullName;	/**< Name of the parameter including the full section name ('/' separated) */
    char				*valstr;	/**< Value of the parameter */
    int					type;
    tdble				valnum;
    char				*unit;		/* for output only */
    tdble				min;
    tdble				max;
    char				**within;
    GF_TAILQ_ENTRY (struct param)	linkParam;	/**< Next parameter in the same section */
} tParam;

GF_TAILQ_HEAD (ParamHead, tParam);
struct section;
GF_TAILQ_HEAD (SectionHead, struct section);

/** Section header structure */
typedef struct section
{
    char				*fullName;	/**< Name of the section including full path ('/' separated) */
    tParamHead				paramList;	/**< List of the parameters of this section */
    GF_TAILQ_ENTRY (struct section)	linkSection;	/**< Next section at the same level */
    tSectionHead			subSectionList;	/**< List of sub-sections (linked by link_section)*/
    struct section			*parent;	/**< Upper section */
} tSection;


#define PARM_MAGIC	0x20030815

/** Configuration header structure */
typedef struct parmHeader 
{
    char	*filename;	/**< Name of the configuration file */
    int		refcount;	/**< Use counter (number of parm handle) */
    tSection	*rootSection;	/**< List of sections at the first level */
    void	*paramHash;	/**< Hash table for parameter access */
    void	*sectionHash;	/**< Hash table for section access */
} tParmHeader;

#define PARM_HANDLE_FLAG_PRIVATE	0x01
#define PARM_HANDLE_FLAG_PARSE_ERROR	0x02


/** Ouput control structure */
typedef struct parmOutput
{
    int		state;
    tSection	*curSection;
    tParam	*curParam;
    char	*indent;
    char	*filename;	/**< Name of the output configuration file */
} tParmOutput;

/** Configuration handle structure */
typedef struct parmHandle
{
    int					magic;
    tParmHeader				*parm;
    char				*val;
    int					flag;
    XML_Parser				parser;
    tSection				*curSection;
    char				*curSectionFullName;
    tParmOutput				outCtrl;
    GF_TAILQ_ENTRY (struct parm_handle)	linkHandle;	/**< Next configuration handle */
} tParmHandle;

GPUL_TAILQ_HEAD (ParmHead, tParmHandle);

#endif /* _PARAMS_H_ */ 



