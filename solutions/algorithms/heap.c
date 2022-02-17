/*******************************************************************/
/*** Implementation of heaps                                     ***/
/*** Functions                                                   ***/
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

/******************** heap_insert() ******************/
/** Insert event '(time,ev)' into heap              **/
/** PARAMETERS: (*)= return-paramter                **/
/**      (*) heap: array containing heap            **/
/**     (*) num_p: ptr to: number of elements       **/
/**          time: time of event                    **/
/*             ev: id of event                      **/
/** RETURNS:                                        **/
/**    nothing                                      **/
/*****************************************************/
void heap_insert(heap_elem_t *heap, int *num_p, double time, int ev)
{
  int pos, parent;                   /* heap positions */
  heap_elem_t elem;          /* for exchangig elements */

  pos = (*num_p);                /* insert at end */
  *num_p = pos+1;
  heap[pos].event = ev;
  heap[pos].t = time;
  parent = (pos-1)/2;
  while((pos > 0)&&                 /* move up in heap */
    (heap[parent].t > heap[pos].t)) 
  {
    elem = heap[parent];       /* exchange parent/child */
    heap[parent] = heap[pos];
    heap[pos] = elem;
    pos = parent;                           /* move up */
    parent = (pos-1)/2;   
  }
}



int main(int argc, char *argv[])
{
  heap_elem_t *heap;
  int heap_size = 100;     /* maximum number of elements */
  int heap_num = 0;        /* current number of elements */
  int t;

  /* create heap: */
  heap = (heap_elem_t *) malloc(heap_size*sizeof(heap_elem_t));

  /* insert some elements */
  heap_insert(heap, &heap_num, 24, 1);
  heap_insert(heap, &heap_num, 21, 2);
  heap_insert(heap, &heap_num, 73, 3);
  heap_insert(heap, &heap_num, 34, 4);
  heap_insert(heap, &heap_num, 98, 5);
  heap_insert(heap, &heap_num, 19, 6);
  heap_insert(heap, &heap_num, 15, 7);
  heap_insert(heap, &heap_num, 29, 8);
  heap_insert(heap, &heap_num, 83, 9);
  heap_insert(heap, &heap_num, 22, 10);
  heap_insert(heap, &heap_num, 41, 11);
  heap_insert(heap, &heap_num, 23, 12);
  heap_insert(heap, &heap_num, 33, 13);

  /* print time of elements level by level, left to right: */
  for(t=0; t<heap_num; t++)
    printf("%f ", heap[t].t);
  printf("\n");

  heap_insert(heap, &heap_num, 17, 14);       /* insert 17 */

  /* print time of elements level by level, left to right: */
  for(t=0; t<heap_num; t++)
    printf("%f ", heap[t].t);
  printf("\n");

  heap_remove(heap, &heap_num, 7);
  for(t=0; t<heap_num; t++)
    printf("%f ", heap[t].t);
  printf("\n");

  heap_remove(heap, &heap_num, 0);
  for(t=0; t<heap_num; t++)
    printf("%f ", heap[t].t);
  printf("\n");


  free(heap);
}
