/*******************************************************************/
/*** Implementation of heaps                                     ***/
/*** Removing of an element (solution of exercise)               ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Trees/Heaps                                        ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "heap.h"



/******************** heap_remove() ******************/
/** Deletes event at position 'pos' from heap       **/
/** PARAMETERS: (*)= return-paramter                **/
/**      (*) heap: array containing heap            **/
/**     (*) num_p: ptr to: number of elements       **/
/**           pos: of element to be removed         **/
/** RETURNS:                                        **/
/**    nothing                                      **/
/*****************************************************/
void heap_remove(heap_elem_t *heap, int *num_p, int pos)
{
  int finished;
  int left, right, parent, min;
  heap_elem_t elem;

  if(pos == (*num_p)-1)       /* last element ? */
  {
    (*num_p)--;
    return;                                 /* finished */
  }
  heap[pos] =          /* put last element at pos */
    heap[--(*num_p)];
  parent = (pos-1)/2;
  if(heap[parent].t > heap[pos].t)             /* case A */
    while((pos > 0)&&                 /* move up in heap */
	  (heap[parent].t > heap[pos].t)) 
    {
      elem = heap[parent];      /* exchange parent/child */
      heap[parent] = heap[pos];
      heap[pos] = elem;
      pos = parent;                           /* move up */
      parent = (pos-1)/2;   
    }
  else                                         /* case B */
  {
    finished = 0;
    while(!finished)     /* move element down until all */
    {                          /* son have higher times */
      left = 2*pos+1;
      right = 2*pos+2;
      if(left >= (*num_p))               /* no children */
      {
	finished = 1;
	break;
      }
      else if(right >= (*num_p))           /* one child */
      {
	min = left;
      }
      else                              /* two children */
      {
	if(heap[left].t < heap[right].t)
	  min = left;
	else
	  min = right;
      }
      if(heap[pos].t < heap[min].t)
      {
	finished = 1;     /* minimum child is NOT lower */
	break;
      }
      elem = heap[pos];             /* exchange pos,min */
      heap[pos] = heap[min];
      heap[min] = elem;
      pos = min;
    }
  }
 
}


