/*******************************************************************/
/*** Function which calculates the mean of n data points         ***/
/*** Test application: mean of exponential distribution          ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Basic data analyis                                 ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************** mean() ********************/
/** Calculates the mean of n data points             **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        n: number of data points                  **/
/**        x: array with data                        **/
/** RETURNS:                                         **/
/**     mean                                         **/
/******************************************************/
double mean(int n, double *x)
{
  double sum = 0.0;                  /* sum of values */
  int i;                                   /* counter */
  
  for(i=0; i<n; i++)     /* loop over all data points */
    sum += x[i];
  return(sum/n);
}

#ifdef ALONE
int main(int argc, char *argv[])
{
  double mu;                           /* parameter of distribution */
  int n=1000;                             /* number of measurements */
  double x[n];                                /* measurement points */
  int i;                                                 /* counter */
  
  mu = 3.0;

  srand48(atoi(argv[1]));       /* set seed according first argument */

  for(i=0; i<n; i++)
    x[i] = -mu * log(1-drand48()); /* generate expon. distr. number */

  printf("# mean: %f\n", mean(n, x));

  return(0);
}
#endif
