/*******************************************************************/
/*** Function which calculates the variance of n data points     ***/
/*** Test application: variance of exponential distribution      ***/
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

/********************** variance() ********************/
/** Calculates the variance of n data points         **/
/** according the "Two-pass algorithm" which includes**/
/** corrections for rounding errors.                 **/
/** see: T.F. Chan, G.H. Golub, and R.J. LeVeque,    **/
/**     Amer. Statist. 37, 242-247 (1983)            **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        n: number of data points                  **/
/**        x: array with data                        **/
/** RETURNS:                                         **/
/**     variance                                     **/
/******************************************************/
double variance(int n, double *x)
{
  double mean = 0.0;                /* mean of values */
  double diff;     /* diff between data point an mean */
  double sum_diff = 0.0,        /* sum of differences */
    sum_diff2 = 0.0;    /* sum of differences squared */
  int i;                                   /* counter */
  
  for(i=0; i<n; i++) /* 1st loop over all data points */
    mean += x[i];
  mean /= n;

  for(i=0; i<n; i++) /* 2nd loop over all data points */
  {
    diff = x[i] - mean;
    sum_diff += diff;
    sum_diff2 += diff*diff;
  }
  /*printf("%e - %e\n", sum_diff2, sum_diff*sum_diff/n);*/
  return( (sum_diff2 - sum_diff*sum_diff/n)/n);
}

#ifdef ALONE
int main(int argc, char *argv[])
{
  double mu,sigma;                     /* parameter of distribution */
  int n=10000000;                         /* number of measurements */
  double u1, u2;                      /* U(0,1) distributed numbers */
  double *x;                                  /* measurement points */
  int i;                                                 /* counter */
  
  sigma = 1;
  mu = 1e14;

  x= (double *) malloc(n*sizeof(double));          /* allocate array*/

  srand48(atoi(argv[1]));      /* set seed according first argument */

  for(i=0; i<n; i+=2)
  {
    u1 = drand48();              /* generate Gaussian distr. number */
    u2 = drand48();
    x[i] = mu+sigma*sqrt(-2.0*log(1-u1))*sin(2*M_PI*u2);
    x[i+1] = mu+sigma*sqrt(-2.0*log(1-u1))*cos(2*M_PI*u2);
  }
  printf("# variance: %e\n", variance(n, x));

  free(x);
  return(0);
}
#endif
