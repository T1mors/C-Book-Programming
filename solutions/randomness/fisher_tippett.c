/*******************************************************************/
/*** Function which returns a random number distributed          ***/
/*** according the Fischer-Tippett distribution                  ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: exercises                                          ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************** rand_fisher_tippett() ***********/
/** Returns random number which is distributed       **/
/** according the Fisher-Tippett distribution        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       lambda: parameter of distribution          **/
/** RETURNS:                                         **/
/**     random number                                **/
/******************************************************/
double rand_fisher_tippett(double lambda)
{
  double u;                            /* random number U(0,1) 0<=1<1 */
  u = drand48();

  return(-log(-log(1.0-u))/lambda);    /* 1-u is also U(0,1) but >0 ! */
}


#ifdef ALONE
int main(int argc, char *argv[])
{
  double lambda;                         /* parameter of distribution */
  int n=10000;                              /* number of measurements */
  double sum;                                   /* measurement points */
  int i;                                                   /* counter */
  
  lambda = 3.0;

  if(argc > 1)
    srand48(atoi(argv[1]));      /* set seed according first argument */

  sum = 0.0;
  for(i=0; i<n; i++)
    sum += rand_fisher_tippett(lambda); /* generate F-T distr. number */

  printf("# mean: %f, expected: %f\n", sum/n, 0.57721/lambda);

  return(0);
}
#endif
