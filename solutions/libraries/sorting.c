/*******************************************************************/
/*** Sorting of an array of double numbers using the stdlib      ***/
/*** function qsort()                                            ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Libraries                                          ***/
/*** Section: Standard C library                                 ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>


/******************* compare_double() *****************/
/** Auxiliary function which compares two numbers.   **/
/** Used to call qsort.                              **/
/** PARAMETERS: (*)= return-paramter                 **/
/**    p1, p2: pointers to the two numbers           **/
/** RETURNS:                                         **/
/**   -1 if *p1<*p2, 0 if *p1=*p2, +1 else           **/
/******************************************************/
int compare_double(const void *p1, const void *p2)
{
  if( *(double *)p1 < *(double *)p2)
    return (-1);
  else if( *(double *)p1 == *(double *)p2 )
    return (0);
  else
    return(1);
}


int main(int argc, char *argv[])
{
  int n=1000;                                   /* number of numbers */
  double val[n];                                            /* array */
  int i;                                                  /* counter */

  for(i=0; i<n; i++)
  {
    val[i] = (double) rand()/RAND_MAX; /* assign random number using */
                                   /* simple random number generator */
  }
  qsort(val, n, sizeof(double), compare_double);

  for(i=0; i<n; i++)                            /* print sorted list */
    printf("%f\n", val[i]);
}


