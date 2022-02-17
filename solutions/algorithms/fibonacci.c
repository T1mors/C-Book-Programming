/*******************************************************************/
/*** Calculates fibonacci numbers using dynamic programming      ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Dynamic programming                                ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************/
/** Calculates Fibonacci number of 'n' defined via                **/
/** fib(1)=1, fib(2)=1, fib(n)=fib(n-1)+fib(n-2) (n>2)            **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**          n: integer number                            
/**                                                               **/
/** Returns:                                                      **/
/**                                                               **/
/*******************************************************************/
double fib(int n)
{
  double *f;            /* stores Fibonacci numbers: f[k]=fib(k+1) */
  int t;                                           /* loop counter */
  double result;

  if(n<3)
    return(1.0);
  else
  {
    f = (double *) malloc(n*sizeof(double));    /* allocate memory */

    f[0] = 1; f[1] = 1;   /* start values for dynammic programming */
    for(t=2; t<n; t++)           /* main loop: dynamic programming */
      f[t] = f[t-1] + f[t-2];
    result = f[n-1];                          /* save final result */

    free(f);
    return(result);
  }
}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n;                        /* argument for fibonnaci function */

  n = atoi(argv[1]);                /* pass n as program parameter */
  printf("fib(%d)=%f\n", n, fib(n));

  return(0);
}
