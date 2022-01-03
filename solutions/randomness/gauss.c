/*******************************************************************/
/*** Prints Gauss distribution G(mu,sigma)                       ***/
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
  double mu;                         /* parameters of distribution */
  double sigma; 
  double x;                                     /* argument of pdf */ 
  double prob;                            /* resulting probability */
  int argz = 1;             /* for treating command line arguments */

  sscanf(argv[argz++], "%lf", &mu);
  sscanf(argv[argz++], "%lf", &sigma);            /* get arguments */

  for(x=-4*sigma+mu; x<=4*sigma+mu; x+=sigma/10)  
  {                          /* iterate to print full distribution */
    prob = exp( -(x-mu)*(x-mu)/(2.0*sigma*sigma))/
      (sigma*sqrt(2*M_PI));
    printf("%f %f\n", x, prob);
  }
  return(0);
}
