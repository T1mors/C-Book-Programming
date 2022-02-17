/*******************************************************************/
/*** Implementation of single-linked lists                       ***/
/*** Removing one element (solution of exercise)                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Lists                                              ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"


/****************** remove_element() **************/
/** Remove element from list                     **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**           elem: to be removed                **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *remove_element(elem_t *list, elem_t *elem)
{
  elem_t *p;
  if(elem == list)                     /* delete first element ? */
  {
    list = elem->next;
  }
  else                         /* delete element not being first */
  {
    p = list;                /* search for element BEFORE 'elem' */
    while( (p != NULL)&&(p->next != elem))
      p = p->next;
    if(p==NULL)
    {
      fprintf(stderr, "element no found\n");
      return(list);
    }
    p->next = elem->next;
  }
  elem->next = NULL;                 /* remove element from list */
  return(list);
}


