/*******************************************************************/
/*** To explain O-notation: summing up n numbers                 ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: O notation                                         ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>


/*******************************************************************/
/** Computes sum of 'n' given real numbers                        **/
/** in array 'number'.                                            **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**        n: # of real numbers                                   **/
/**   number: array to be added up                                **/
/**                                                               **/
/** Returns:                                                      **/
/**        sum                                                    **/
/*******************************************************************/
double compute_sum(int n, double *number)
{
  double sum=0.0;                                /* for summing up */
  int t;                                         /* loop counter   */

  for(t=0; t<n; t++)                                  /* main loop */
    sum += number[t];

  return(sum);
}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n=100;                                  /* number of numbers */
  double *number;                /* array where numbers are stored */
  int t;                                  /* loop counter   */

  number = (double *) malloc(n*sizeof(double));  /* reserve memory */

  for(t=0; t<n; t++)               /* fill array with some numbers */
    number[t] = t;    
  
  printf("sum = %f\n", compute_sum(n, number));         /* do call */

  free(number);                                     /* free memory */

  return(0);
}
