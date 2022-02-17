/*******************************************************************/
/*** Prints pdf of Fisher-Tippett distribution                   ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Introduction to probability                        ***/
/*******************************************************************/

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  double lambda;                      /* parameter of distribution */
  double x;                                     /* argument of pdf */ 
  double prob;                            /* resulting probability */
  int argz = 1;             /* for treating command line arguments */

  sscanf(argv[argz++], "%lf", &lambda);            /* get argument */

  for(x=-2*lambda; x<=20*lambda; x+=lambda/10)  
  {                          /* iterate to print full distribution */
    prob = lambda*exp(-lambda*x)*exp(-exp(-lambda*x));
    printf("%f %e\n", x, prob);
  }
  return(0);
}
