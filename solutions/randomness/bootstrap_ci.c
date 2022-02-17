/*******************************************************************/
/*** Function which calculates a confidence interval             ***/
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


/******************* compare_double() *****************/
/** Auxiliary functin which compares two number      **/
/** Used to call qsort                               **/
/** PARAMETERS: (*)= return-paramter                 **/
/**    p1, p2: pointers to the two numbers           **/
/** RETURNS:                                         **/
/**   -1 if *p1<*p2, 0 if *p1=*p2, +1 else           **/
/******************************************************/
int compare_double(const void *p1, const void *p2)
{
  if( *(double *)p1 < *(double *)p2)
    return (-1);
  else if( *(double *)p1 == *(double *)p2)
    return (0);
  else
    return(1);
}



/***************** bootstrap_ci() *********************/
/** Calculates a confidence interval by 'n_resample' **/
/** times resampling the given sample points         **/
/** and each time evaluation the estimator 'f'       **/
/** PARAMETERS: (*)= return-paramter                 **/
/**           n: number of data points               **/
/**           x: array with data                     **/
/**  n_resample: number of bootstrap iterations      **/
/**       alpha: confidence level                    **/
/**           f: function (pointer) = estimator      **/
/**     (*) low: (p. to) lower boundary of conf. int.**/
/**    (*) high: (p. to) upper boundary of conf. int.**/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
void bootstrap_ci(int n, double *x, int n_resample,
		  double alpha, double (*f)(int, double *),
		  double *low, double *high)
{
  double *xb;                                    /* bootstrap sample */
  double *h;                              /* results from resampling */
  int sample, i;                                    /* loop counters */
  int k;                                          /* sample point id */

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

  qsort(h, n_resample, sizeof(double), compare_double);
  *low = h[(int) floor(n_resample*alpha/2)];  /* obtain conf. interval */
  *high = h[(int) floor(n_resample*(1-alpha/2))];
  free(h);
  free(xb);
}

