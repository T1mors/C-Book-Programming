/*******************************************************************/
/*** Calculates the power of a given number using a              ***/
/*** divide-and-conquer approach                                 ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Divide and Conquer                                 ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******************* fast_power() **************************/
/** Caluclates the a^n (n being a natural number) using   **/
/** a divide-and-conquer approach.                        **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**            a: base                                    **/
/**            n: power                                   **/
/** Returns:                                              **/
/**        a^n                                            **/
/***********************************************************/
double fast_power(double a, int n)
{
  if(n<0)                       /* extension to negative powers */
    return(1.0/fast_power(a, -n));
  else if(n==0)                                /* trivial cases */
    return(1.0);
  else if(n==1)
    return(a);
  else
  {
    double tmp;

    tmp=fast_power(a, n/2);
    if(n%2)                                 /* if n is odd */
      return(tmp*tmp*a);
    else
      return(tmp*tmp);
  }
}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  double a;                                                /* base */
  int n;                                                  /* power */

  sscanf(argv[1], "%lf", &a);                   /* read parameters */
  n = atoi(argv[2]);

  printf("%f^%d=%e\n", a, n, fast_power(a, n));  /* print result */
}
