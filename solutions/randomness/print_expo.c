/*******************************************************************/
/*** Prints exponential distribution                             ***/
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
  double mu;                          /* parameter of distribution */
  double x;                                     /* argument of pdf */ 
  double prob;                            /* resulting probability */
  int argz = 1;             /* for treating command line arguments */

  sscanf(argv[argz++], "%lf", &mu);                /* get argument */

  for(x=0; x<=6*mu; x+=mu/10)  
  {                          /* iterate to print full distribution */
    prob = exp( -x/mu)/mu;
    printf("%f %f\n", x, prob);
  }
  return(0);
}
