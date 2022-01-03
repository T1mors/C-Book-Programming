/*******************************************************************/
/*** Implementation of heaps                                     ***/
/*** Header file                                                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Trees/Heaps                                        ***/
/*******************************************************************/



#ifndef _HEAP_H_

/** macros **/

/** data types **/
/** heap stores events: one element: **/
typedef struct
{
  double     t;                /* time of event */
  int    event;                  /* id of event */
} heap_elem_t;

/** function prototypes **/
extern void heap_remove(heap_elem_t *heap, int *num_p, int pos);


#endif /* ifndef */
