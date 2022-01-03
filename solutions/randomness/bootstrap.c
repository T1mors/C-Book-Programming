/*******************************************************************/
/*** Function which calculates an estimator for the error bar    ***/
/*** of an arbitrary estimator via the boostrap approach         ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Resampling using bootstrap                         ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "analysis.h"

/************* bootstrap_variance() *******************/
/** Calculates the variance from 'n_resample'        **/
/** times resampling the given sample points         **/
/** and each time evaluation the estimator 'f'       **/
/** PARAMETERS: (*)= return-paramter                 **/
/**           n: number of data points               **/
/**           x: array with data                     **/
/**  n_resample: number of bootstrap iterations      **/
/**           f: function (pointer) = estimator      **/
/** RETURNS:                                         **/
/**     variance                                     **/
/******************************************************/
double bootstrap_variance(int n, double *x, int n_resample,
			 double (*f)(int, double *))
{
  double *xb;                                    /* bootstrap sample */
  double *h;                              /* results from resampling */
  int sample, i;                                    /* loop counters */
  int k;                                          /* sample point id */
  double var;                              /* result to be returned */

  h = (double *) malloc(n_resample * sizeof(double));
  xb = (double *) malloc(n * sizeof(double));
  for(sample=0; sample<n_resample; sample++)
  {
    for(i=0; i<n; i++)                                   /* resample */
    {
      k = (int) floor(drand48()*n);           /* select random point */
      xb[i] = x[k];
    }
    h[sample] = f(n, xb);                     /* calculate estimator */
  }

  var = variance(n_resample, h);        /* obtain bootstrap variance */
  free(h);
  free(xb);
  return(var);
}

