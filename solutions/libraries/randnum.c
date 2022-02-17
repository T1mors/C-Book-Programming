/*******************************************************************/
/*** Generates random numbers                                    ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Libraries                                          ***/
/*** Section: gnu scientific library                             ***/
/*******************************************************************/

#include <stdio.h>
#include <gsl/gsl_rng.h>

int main()
{
  gsl_rng *rng;            /* pointer to a random number generator */
  int n = 100;                         /* number of random numbers */
  int i;                                           /* loop counter */
  double r;                                     /* a random number */

  rng = gsl_rng_alloc(gsl_rng_mt19937);      /* allocate generator */
  gsl_rng_set(rng, 1000);                      /* set seed to 1000 */

  for(i=0; i<n; i++)                           /* generate numbers */
  {
    r = gsl_rng_uniform(rng);
    printf("%4.3f\n", r);
  }

  gsl_rng_free(rng);                           /* delete generator */

  return(0);
}
