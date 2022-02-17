/*******************************************************************/
/*** Sorting of an array of (x,y) vectors  using the stdlib      ***/
/*** function qsort()                                            ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Libraries                                          ***/
/*** Section: Exercises                                          ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/** type for two-dimensional vectors (x,y) **/
typedef struct
{
  double x,y;                   /* elements of vector */
} vector_t;


/******************* compare_vector() *****************/
/** Auxiliary function which compares two vectors    **/
/** by its length.                                   **/
/** Used to call qsort.                              **/
/** PARAMETERS: (*)= return-paramter                 **/
/**    p1, p2: pointers to the two vectors           **/
/** RETURNS:                                         **/
/**   -1 if *p1<*p2, 0 if *p1=*p2, +1 else           **/
/******************************************************/
int compare_vector(const void *p1, const void *p2)
{
  vector_t v1, v2;                                    /* vectors */
  double l1s,l2s;                  /* lengths of vectors squared */

  v1 = *(vector_t *) p1;  /* tranfer to variable for readability */
  v2 = *(vector_t *) p2; 

  l1s = (v1.x*v1.x + v1.y*v1.y);            /* calculate lengths */
  l2s = (v2.x*v2.x + v2.y*v2.y);

  if(l1s < l2s)                               /* compare lengths */
    return (-1);
  else if(l1s == l2s)
    return (0);
  else
    return(1);
}


int main(int argc, char *argv[])
{
  int n=1000;                                   /* number of vectors */
  vector_t val[n];                                          /* array */
  int i;                                                  /* counter */

  for(i=0; i<n; i++)
  {
    val[i].x = (double) rand()/RAND_MAX; /* assign random number using */
                                     /* simple random number generator */
    val[i].y = (double) rand()/RAND_MAX;
  }
  qsort(val, n, sizeof(vector_t), compare_vector);

  for(i=0; i<n; i++)                            /* print sorted list */
    printf("(%f,%f)\n", val[i].x, val[i].y);
}


