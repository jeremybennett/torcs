/***************************************************************************

    file                 : ringlist.cpp
    created              : Wed Feb 23 20:14:08 CET 2000
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

/** @file
    		Ring list management.
		The ring lists are linked lists without end, the tail is linked to the head.
		The list pointer is on the tail, so the access to the head is list->next.
		The first two fields of the elements are always next and prev.
    		
    @author	<a href=mailto:torcs@free.fr>Eric Espie</a>
    @version	$Id$
    @ingroup	ringlist
*/
#ifdef WIN32
#include <windows.h>
#endif
#include <tgf.h>

void gfRlstInit(void)
{
}


/** Initialize the ring list head.
    @ingroup	ringlist
    @param	head	Ring list to initialize.
    @return	None
    @warning	Using uninitialized list leads to unpredictable behaviour.
*/
void
GfRlstInit(tRingListHead *head)
{
    head->next = (tRingList*)head;
    head->prev = (tRingList*)head;
}


/** Add an element in first position of a double link ring list.
    @ingroup	ringlist
    @param	head List where the element is inserted
    @param	elt Element to instert
*/
void 
GfRlstAddFirst(tRingListHead *head, tRingList *elt)
{
    elt->next = head->next;
    head->next = elt;
    elt->prev = (tRingList*)head;
    elt->next->prev = elt;
}

/** Add an element in last position of a double link ring list.
    @ingroup	ringlist
    @param	head List where the element is inserted
    @param	elt Element to instert
*/
void 
GfRlstAddLast(tRingListHead *head, tRingList *elt)
{
    elt->next = (tRingList*)head;
    elt->prev = head->prev;
    head->prev = elt;
    elt->prev->next = elt;
}

/** Unlink the first element of a ring list.
    @ingroup	ringlist
    @param	head List where the element is to be unlinked
    @return	Unlinked element
*/
tRingList *
GfRlstUnlinkFirst(tRingListHead *head)
{
    if (head->next == (tRingList*)head) {
	return (tRingList*)NULL;
    }
    return GfRlstUnlinkElt(head->next);
}

/** Unlink the last element of a ring list.
    @ingroup	ringlist
    @param	head List where the element is to be unlinked
    @return	Unlinked element
*/
tRingList *
GfRlstUnlinkLast(tRingListHead *head)
{
    if (head->next == (tRingList*)head) {
	return (tRingList*)NULL;
    }
    return GfRlstUnlinkElt(head->prev);
}

/** Unlink an element of a double link ring list.
    @ingroup	ringlist
    @param	elt  Element to unlink
    @return	Unlinked element
*/
inline tRingList *
GfRlstUnlinkElt(tRingList *elt)
{
    elt->prev->next = elt->next;
    elt->next->prev = elt->prev;
    elt->prev = (tRingList*)NULL;
    elt->next = (tRingList*)NULL;

    return elt;
}

/** Get the first element of a ring list without unlinking it.
    @ingroup	ringlist
    @param	head	Current ring list
    @return	The first element (or NULL if empty)
*/
tRingList *
GfRlstGetFirst(tRingListHead *head)
{
    if (head->next == (tRingList*)head) {
	return (tRingList*)NULL;
    }
    return head->next;
}

/** Get the last element of a ring list without unlinking it.
    @ingroup	ringlist
    @param	head	Current ring list
    @return	The last element (or NULL if empty)
*/
tRingList *
GfRlstGetLast(tRingListHead *head)
{
    if (head->prev == (tRingList*)head) {
	return (tRingList*)NULL;
    }
    return head->prev;
}

/** Get the next element of a ring list without unlinking it.
    @ingroup	ringlist
    @param	head	Current ring list
    @param	elt  	Element to get the next one
    @return	The next element (or NULL if elt is last)
*/
tRingList *
GfRlstGetNext(tRingListHead *head, tRingList *elt)
{
    tRingList *next = elt->next;
    if (next == (tRingList*)head) {
	return (tRingList*)NULL;
    }
    return next;
}

/** Get the previous element of a ring list without unlinking it.
    @ingroup	ringlist
    @param	head	Current ring list
    @param	elt  	Element to get the previous one
    @return	The previous element (or NULL if elt is last)
*/
tRingList *
GfRlstGetPrev(tRingListHead *head, tRingList *elt)
{
    tRingList *prev = elt->prev;
    if (prev == (tRingList*)head) {
	return (tRingList*)NULL;
    }
    return prev;
}

/** Set the head before the specified element
    @ingroup	ringlist
    @param	head	Current ring list
    @param	elt	Element to become the first of the list
    @return	<tt>0 ... </tt>Ok
		<br><tt>-1 .. </tt>Error
 */
void
GfRlstSeekElt(tRingListHead *head, tRingList *elt)
{
    /* fisrt unlink the head */
    head->next->prev = head->prev;
    head->prev->next = head->next;
    
    /* now insert the head before the element */
    head->prev = elt->prev;
    elt->prev = (tRingList*)head;
    head->next = elt;
    head->prev->next = (tRingList*)head;
}

