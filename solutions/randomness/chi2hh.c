/*******************************************************************/
/*** Generates random numbers for two (different) binomial       ***/
/*** distribution and compares them via the chi2 test            ***/
/***                                                             ***/
/*** Solutuion to exercise from the book:                        ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Hypothesis testing and (in-)dependence of data     ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>

/********************* chi2_hh() ***********************/
/** For chi^2 test: comparison of two histograms      **/
/** to probabilities: Probability to                  **/
/** obtain the corresponding  chi2 value or worse.    **/
/** It is assumed that the total number of data points**/
/*+ in the two histograms is equal !                  **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**  n_bins: number of bins                           **/
/**       h: array of histogram values                **/
/**      h2: 2nd array of histogram values            **/
/**                                                   **/
/** Returns:                                          **/
/**       p-value                                     **/
/*******************************************************/
double chi2_hh(int n_bins, int *h, int *h2)
{
  int n, n2;                  /* total number of sample points */
  double chi2;                                  /* chi^2 value */
  int K_prime;                  /* number of contributing bins */
  int i;                                            /* counter */

  n = 0; n2 = 0;    /* calculate total number of sample_points */
  for(i=0; i<n_bins; i++)
  {
    n += h[i];
    n2 += h2[i];
  }
  
  if(n != n2)
  {
    fprintf(stderr, "chi2 test: number of samples points no equal!");
    return(0.0);
  }

  chi2 = 0.0; K_prime = 0;
  for(i=0; i<n_bins; i++)                   /* calculate chi^2 */
  {
    if( (h[i] > 0)&&(h2[i] > 0) )
    {
      chi2 += (double) (h[i]-h2[i])*(h[i]-h2[i])/(h[i]+h2[i]);
      K_prime ++;
    } 
  }
  return(gsl_cdf_chisq_Q(chi2, K_prime-1));
}


int main()
{
  gsl_rng *rng;            /* pointer to a random number generator */
  int num_r = 100;                     /* number of random numbers */
  int i;                                           /* loop counter */
  int par_n;                 /* parameter of binomial distribution */
  double par_p;              /* parameter of binomial distribution */
  double r;                                     /* a random number */
  int num_bins = 30;                /* number of bins of histogram */
  int h[num_bins];                          /* poor mans histogram */
  int h2[num_bins];                         /* poor mans histogram */

  rng = gsl_rng_alloc(gsl_rng_mt19937);      /* allocate generator */
  gsl_rng_set(rng, 1000);                      /* set seed to 1000 */

  par_n = 10;

  for(i=0; i<num_bins; i++)                    /* reset histograms */
    h2[i] = 0;
  for(i=0; i<num_r; i++)                       /* generate numbers */
  {
    r = (double) gsl_ran_binomial(rng, 0.5, par_n);
      h2[(int) r]++;
  }


  for(par_p=0.05; par_p<0.95; par_p+=0.05)
  { 
    for(i=0; i<num_bins; i++)                  /* reset histograms */
    {
      h[i] = 0;
    }

    for(i=0; i<num_r; i++)                     /* generate numbers */
    {
      r = (double) gsl_ran_binomial(rng, par_p, par_n);
      h[(int) r]++;
    }

    printf("Q(%f)= %e\n", par_p, chi2_hh(par_n+1, h, h2));
  }
  gsl_rng_free(rng);                               /* delete stuff */
  return(0);
}
