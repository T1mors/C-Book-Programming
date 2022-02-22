/*******************************************************************/
/*** Implementation of single-linked lists                       ***/
/*** Sort list using mergesort (solution of exercise)            ***/
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



/***************** mergesort_list() ***************/
/** Sorts list using mergesort algorithm         **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *mergesort_list(elem_t *list)
{
  elem_t *aux;                         /* auxiliary list pointer */
  elem_t *list1,*list2;       /* pointer to 1st/2nd half of list */
  int length, length1;         /* of full list/ 1st half of list */

  length = 0;                        /* determine length of list */
  aux = list;
  while(aux != NULL)
  {
    length++;
    aux = aux->next;
  }

  if(length == 1)          /* one element list is already sorted */
    return(list);

  length1 = 0;          /* move 'list2' to beginning of 2nd half */
  list2 = list;
  while(length1 < length/2)
  {
    length1 ++;
    aux = list2;
    list2 = list2->next;
  }       /* now 'aux' just points to one element before 'list2' */ 
  aux->next = NULL;                            /* decouple lists */
  
  list1 = mergesort_list(list);            /* sort partial lists */
  list2 = mergesort_list(list2);

  if(list1->info < list2->info)   /* start merged (=sorted) list */
  {
    list = list1;
    list1 = list1->next;
  }
  else
  {
    list = list2;
    list2 = list2->next;
  }
  aux = list;        /* aux points to current end of sorted list */
  while( (list1 != NULL)||(list2 != NULL))        /* merge lists */
  {
    if( (list1 == NULL)||((list2!=NULL)&&(list2->info<list1->info)))
    {                /* move element from 'list2' to sorted list */
      aux->next=list2;
      aux=list2;
      list2 = list2->next;
    }
    else
    {                /* move element from 'list1' to sorted list */
      aux->next=list1;
      aux=list1;
      list1 = list1->next;
    }
  }
  aux->next =NULL;      

  return(list);
}
