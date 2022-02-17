/*******************************************************************/
/*** Calculates the factorial of a number using a                ***/
/*** using a sequential approach                                 ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Iteration and recursion                            ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************/
/** Calculates the factorial of a number                          **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**            n: number                                          **/
/**                                                               **/
/** Returns:                                                      **/
/**         factorial(n)                                          **/
/*******************************************************************/
int factorial(int n)
{
  int t;                                           /* loop counter */
  int fac;                                               /* result */ 

  fac = 1;
  for(t=2; t<=n; t++)                                 /* main loop */
    fac *= t;

  return(fac);
}


/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n;            /* number of which factorial is to be computed */    

  n = atoi(argv[1]);             /* n= first command line argument */
  printf("factorial(%d)=%d\n", n, factorial(n));
  return(0);
}
