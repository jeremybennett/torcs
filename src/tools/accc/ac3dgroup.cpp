/***************************************************************************

    file                 : ac3dto3ds.cpp
    created              : Sat Mar 31 09:27:43 CET 2001
    copyright            : cg
    email                : 
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
    		
    @author	
    @version	$Id$
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <math.h>

#include "accc.h"


extern int printOb(ob_t * ob);
extern mat_t * root_material;
extern void smoothTriNorm(ob_t * object ); 
void loadAndGroup( char *OutputFileName)
{
  ob_t * ob0=NULL;
  ob_t * ob1=NULL;
  ob_t * ob2=NULL;
  ob_t * ob3=NULL;
  ob_t * tmpob=NULL;
  ob_t * tmpob2=NULL;
  mat_t * tmat=NULL;
  int requiredExtraGroup=0;
  extern FILE * ofile;
  int num_tkmn=0;
  ob_groups_t * array_groups;
  int good_group=0;
  int i=0;
  double dist=0;

  if (fileL0)
    {
      fprintf(stderr,"\nloading file %s\n",fileL0);
      loadAC(fileL0,NULL,-1);
      ob0=root_ob;
      root_ob=NULL;
    }
  if (fileL1)
    {
      fprintf(stderr,"\nloading file %s\n",fileL1);
      loadAC(fileL1,NULL,-1);
      ob1=root_ob;
      root_ob=NULL;
    }
  if (fileL2)
    {
      fprintf(stderr,"\nloading file %s\n",fileL2);
      loadAC(fileL2,NULL,-1);
      ob2=root_ob;
      root_ob=NULL;
    }
  if (fileL3)
    {
      fprintf(stderr,"\nloading file %s\n",fileL3);
      loadAC(fileL3,NULL,-1);
      ob3=root_ob;
      root_ob=NULL;
    }
  /* now collapse the texture and texture  arrays of 1 2 3 in 0 */

  smoothTriNorm(ob0);
  
  printf("collapsing textures \n");
  fprintf(stderr,"\ncollapsing textures\n");
  tmpob=ob0;
  while (tmpob!=NULL) {
    if (tmpob->name==NULL)  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "root"))  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "world")){
      tmpob=tmpob->next;
      continue;
    }
     
    tmpob2=ob1;
    while (tmpob2!=NULL) {
      if (tmpob2->name==NULL)  {
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, "root"))  {
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, "world")){
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, tmpob->name) && tmpob->numvert==tmpob2->numvert)
	{
	  /* found an ob in ob1 */
	  tmpob->texture1=tmpob2->texture;
	  tmpob->textarray1=tmpob2->textarray;
	  tmpob->vertexarray1=tmpob2->vertexarray;
	  break;
	}
      tmpob2=tmpob2->next;
    }

    tmpob2=ob2;
    while (tmpob2!=NULL) {
      if (tmpob2->name==NULL)  {
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, "root"))  {
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, "world")){
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, tmpob->name) && tmpob->numvert==tmpob2->numvert)
	{
	  /* found an ob in ob2 */
	  tmpob->texture2=tmpob2->texture;
	  tmpob->textarray2=tmpob2->textarray;
	  tmpob->vertexarray2=tmpob2->vertexarray;
	  break;
	}
      tmpob2=tmpob2->next;
    }

    tmpob2=ob3;
    while (tmpob2!=NULL) {
      if (tmpob2->name==NULL)  {
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, "root"))  {
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, "world")){
	tmpob2=tmpob2->next;
	continue;
      }
      if (!strcmp(tmpob2->name, tmpob->name) && tmpob->numvert==tmpob2->numvert)
	{
	  /* found an ob in ob2 */
	  tmpob->texture3=tmpob2->texture;
	  tmpob->textarray3=tmpob2->textarray;
	  tmpob->vertexarray3=tmpob2->vertexarray;
	  if(tmpob->texture3)
	    for (i=0; i<tmpob->numvert; i++)
	      {
		if (tmpob->textarray3[i*2]!=tmpob->textarray[i*2] 
		    || tmpob->textarray3[i*2+1]!=tmpob->textarray[i*2+1])
		  printf("name=%s %.2lf!=%.2lf %.2lf!=%.2lf\n",tmpob->name,tmpob->textarray[i*2],
			 tmpob->textarray3[i*2],tmpob->textarray[i*2+1],tmpob->textarray3[i*2+1]); 
	      }
	   
	  break;
	}
      tmpob2=tmpob2->next;
    }
    tmpob=tmpob->next;
  }
  /* now make groups from ob0 */

   
  fprintf(stderr,"making groups\n");
  tmpob=ob0;
  num_tkmn=0;
  while (tmpob!=NULL) {
    if (tmpob->name==NULL)  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "root"))  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "world")){
      tmpob=tmpob->next;
      continue;
    }
    if (!strnicmp(tmpob->name, "tkmn",4) && strcmp(tmpob->type,"group")){
      tmpob=tmpob->next;
      num_tkmn++;
      continue;
    }
    
    tmpob=tmpob->next;
  }
   
  printf("found %d tkmn\n",num_tkmn);
  if (num_tkmn==0)
    {
      fprintf(stderr,"\nERROR: cannot find any object tkmn for grouping\nAborting\n");
      exit (-1);
    }

  i=0;
  tmpob=ob0;
  array_groups=(ob_groups_t *) malloc(sizeof(ob_groups_t)*num_tkmn);
  while (tmpob!=NULL) {
    if (tmpob->name==NULL)  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "root"))  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "world")){
      tmpob=tmpob->next;
      continue;
    }
    if (!strnicmp(tmpob->name, "tkmn",4) && strcmp(tmpob->type,"group")){
      array_groups[i].tkmn=tmpob;
      array_groups[i].numkids=1;
      array_groups[i].name=tmpob->name;
      array_groups[i].kids=NULL;
      array_groups[i].kids0=NULL;
      array_groups[i].kids1=NULL;
      array_groups[i].kids2=NULL;
      array_groups[i].kids3=NULL;
      array_groups[i].numkids0=0;
      array_groups[i].numkids1=0;
      array_groups[i].numkids2=0;
      array_groups[i].numkids3=0;
      tmpob=tmpob->next;
      i++;
      continue;
    }
    tmpob=tmpob->next;
  }

  fprintf(stderr,"dispatching objects in groups\n");
  tmpob=ob0;
  while (tmpob!=NULL) {
    if (tmpob->name==NULL)  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "root"))  {
      tmpob=tmpob->next;
      continue;
    }
    if (!strcmp(tmpob->name, "world")){
      tmpob=tmpob->next;
      continue;
    }
    if (!strnicmp(tmpob->name, "tkmn",4)){
      tmpob=tmpob->next;
      continue;
    }

    good_group=-1;
    tmpob->dist_min=1000000;
    for (i=0; i<num_tkmn; i++)
      {
	dist=findDistmin( array_groups[i].tkmn, tmpob);
	if (dist<tmpob->dist_min)
	  {
	    tmpob->dist_min=dist;
	    good_group=i;
	  }
      }
    if (good_group==-1)
      {
	printf("an object in no group %s \n",tmpob->name);
	tmpob=tmpob->next;
	continue;
      }
    printf("object %s is going to group %s  at dist=%f\n",tmpob->name,
	   array_groups[good_group].name,sqrt(tmpob->dist_min));
    if (array_groups[good_group].kids==NULL)
      {
	array_groups[good_group].kids=tmpob;
	tmpob=tmpob->next;
	array_groups[good_group].numkids++;
	array_groups[good_group].kids->next=NULL;
      }
    else
      {
	tmpob2=array_groups[good_group].kids;
	array_groups[good_group].kids=tmpob;
	tmpob=tmpob->next;
	array_groups[good_group].kids->next=tmpob2;
	array_groups[good_group].numkids++;
      }

    /*tmpob=tmpob->next;*/
  }
  /* now each tkmn group contains the list of its kids */

   /* for all tkmn groups the kids are dispatched in the different group levels */

#define INSERTINGROUP(kids,ob)   {\
     ob->next=kids;\
     kids=ob;\
   }
	 
  for (i=0; i<num_tkmn; i++)
    {
      ob_t * tmpobnext;
      tmpob=array_groups[i].kids;
      printf("grouping level for %s\n", array_groups[i].name);
      while (tmpob!=NULL) {
	tmpobnext=tmpob->next;
	if (tmpob->name==NULL)  {
	  tmpob=tmpobnext;
	  continue;
	}
	if (!strnicmp(tmpob->name, "tkrb",4)){
	  array_groups[i].numkids--;
	  array_groups[i].numkids0++;
	  INSERTINGROUP(array_groups[i].kids0,tmpob);
	  printf("inserting %s in group 0 of %s\n",tmpob->name, array_groups[i].name);
	  tmpob=tmpobnext;
	  continue;
	}
	if (!strnicmp(tmpob->name, "tklb",4)){
	  array_groups[i].numkids--;
	  array_groups[i].numkids0++;
	  INSERTINGROUP(array_groups[i].kids0,tmpob);
	  printf("inserting %s in group 0 of %s\n",tmpob->name, array_groups[i].name);
	  tmpob=tmpobnext;	  
	  continue;
	}
	if (!strnicmp(tmpob->name, "tkrs",4)){
	  array_groups[i].numkids--;
	  array_groups[i].numkids0++;
	  INSERTINGROUP(array_groups[i].kids0,tmpob);
	  printf("inserting %s in group 0 of %s\n",tmpob->name, array_groups[i].name);
	  tmpob=tmpobnext;
	  continue;
	}
	if (!strnicmp(tmpob->name, "tkls",4)){
	  array_groups[i].numkids--;
	  array_groups[i].numkids0++;
	  INSERTINGROUP(array_groups[i].kids0,tmpob);
	  printf("inserting %s in group 0 of %s\n",tmpob->name, array_groups[i].name);
	  tmpob=tmpobnext;
	  continue;
	}
	
	if (tmpob->dist_min<d1*d1)
	  {
	    array_groups[i].numkids--;
	    array_groups[i].numkids1++;
	    INSERTINGROUP(array_groups[i].kids1,tmpob);
	    printf("inserting %s in group 1 of %s\n",tmpob->name, array_groups[i].name);
	  }
	else
	  if (tmpob->dist_min<d2*d1)
	    {
	      array_groups[i].numkids--;
	      array_groups[i].numkids2++;
	      INSERTINGROUP(array_groups[i].kids2,tmpob);
	      printf("inserting %s in group 2 of %s\n",tmpob->name, array_groups[i].name);
	    }
	  else
	    if (tmpob->dist_min<d3*d3)
	      {
		array_groups[i].numkids--;
		array_groups[i].numkids3++;
		INSERTINGROUP(array_groups[i].kids3,tmpob);
		printf("inserting %s in group 3 of %s\n",tmpob->name, array_groups[i].name);
	      }
	    else
	      {
		printf("cannot insert object %s in group %s\n",tmpob->name,array_groups[i].name);
		requiredExtraGroup=1;
	      }
	/*if (!strnicmp(tmpob->name, "tk",2)){
	  tmpob2=tmpob;
	  tmpob=tmpob->next;
	  continue;
	  }*/
	 
	tmpob=tmpobnext;
      }
      if (array_groups[i].numkids==0)
	array_groups[i].kids=NULL;
      printf("in group %s\n",array_groups[i].name);
      printf("    found in l0  %d\n",array_groups[i].numkids0);
      printf("    found in l1  %d\n",array_groups[i].numkids1);
      printf("    found in l2  %d\n",array_groups[i].numkids2);
      printf("    found in l3  %d\n",array_groups[i].numkids3);
      printf("    staying kids  %d\n",array_groups[i].numkids-1); /* because of the tkmn not moved */


    }

#ifdef NEWSRC
  for (i=0; i<num_tkmn; i++)
    {
      if (array_groups[i].numkids3>0)
	{
	  mergeSplitted(&(array_groups[i].kids3));
	}
      if (array_groups[i].numkids2>0)
	{
	  mergeSplitted(&(array_groups[i].kids2));
	}
      if (array_groups[i].numkids1>0)
	{
	  mergeSplitted(&(array_groups[i].kids1));
	}
    }
#endif


  fprintf(stderr,"writing destination file %s\n",OutputFileName);



  if ((ofile=fopen (OutputFileName,"w"))==NULL) 
    {
      fprintf(stderr,"failed to open %s\n", OutputFileName);
      return ;
    }
  fprintf(ofile,"AC3Db\n");
  tmat=root_material->next;
  while (tmat!=NULL)
    {
      fprintf(ofile, "MATERIAL %s rgb %1.2f %1.2f %1.2f amb %1.2f %1.2f %1.2f emis %1.2f %1.2f %1.2f spec %1.2f %1.2f %1.2f shi %3d trans 0 \n",
	      tmat->name,
	      tmat->rgb.r,
	      tmat->rgb.g,
	      tmat->rgb.b,
	      tmat->amb.r,
	      tmat->amb.g,
	      tmat->amb.b,
	      tmat->emis.r,
	      tmat->emis.g,
	      tmat->emis.b,
	      tmat->spec.r,
	      tmat->spec.g,
	      tmat->spec.b,
	      (int)tmat->shi);
	      /*(int)tmat->trans);*/
      tmat=tmat->next;
    }
  
  fprintf(ofile,"OBJECT world\n");
  fprintf(ofile,"kids %d\n",num_tkmn);
  
  for (i=0; i<num_tkmn; i++)
    {
      int numg=0;
      fprintf(ofile,"OBJECT group\n");
      fprintf(ofile,"name \"%s_g\"\n",array_groups[i].tkmn->name);
      numg=(array_groups[i].kids3==0?0:1)+(array_groups[i].kids2==0?0:1)+(array_groups[i].kids1==0?0:1)+1;
      fprintf(ofile,"kids %d\n",numg);
      /*printOb(array_groups[i].tkmn);*/


      if (array_groups[i].numkids3>0)
	{
	  fprintf(ofile,"OBJECT group\n");
	  fprintf(ofile,"name \"___%s_gl3\"\n",array_groups[i].tkmn->name);
	  fprintf(ofile,"kids %d\n",array_groups[i].numkids3);
	  printf("writting group: ___%s_gl3\n",array_groups[i].tkmn->name);
	  tmpob=array_groups[i].kids3;
	  while (tmpob!=NULL)
	    {

	      printOb(tmpob);
	      printf("%s\n",tmpob->name);
	      tmpob=tmpob->next;
	    }
	}

      if (array_groups[i].numkids2>0)
	{
	  fprintf(ofile,"OBJECT group\n");
	  fprintf(ofile,"name \"%%___%s_gl2\"\n",array_groups[i].tkmn->name);
	  fprintf(ofile,"kids %d\n",array_groups[i].numkids2);
	  printf("writting group: ___%s_gl2\n",array_groups[i].tkmn->name);
	  tmpob=array_groups[i].kids2;
	  while (tmpob!=NULL)
	    {
	      printOb(tmpob);
	      printf("%s\n",tmpob->name);
	      tmpob=tmpob->next;
	    }
	}
      if (array_groups[i].numkids1>0)
	{
	  fprintf(ofile,"OBJECT group\n");
	  fprintf(ofile,"name \"___%s_gl1\"\n",array_groups[i].tkmn->name);
	  fprintf(ofile,"kids %d\n",array_groups[i].numkids1);
	  printf("writting group: ___%s_gl1\n",array_groups[i].tkmn->name);
	  tmpob=array_groups[i].kids1;
	  while (tmpob!=NULL)
	    {
	      printOb(tmpob);
	      printf("%s\n",tmpob->name);
	      tmpob=tmpob->next;
	    }
	}
     
      /* there is always a group 0 with the tkmn at leat */
      fprintf(ofile,"OBJECT group\n");
      fprintf(ofile,"name \"___%s_gl0\"\n",array_groups[i].tkmn->name);
      fprintf(ofile,"kids %d\n",array_groups[i].numkids0+1);
      printf("writting group: ___%s_gl0\n",array_groups[i].tkmn->name);
      tmpob=array_groups[i].kids0;
      while (tmpob!=NULL)
	{
	  printOb(tmpob);
	  printf("%s\n",tmpob->name);
	  tmpob=tmpob->next;
	}
      printOb(array_groups[i].tkmn);
    }
  
	 
	       
  return ;
}




