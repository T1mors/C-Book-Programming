/*******************************************************************/
/*** Generates random numbers according binomial distribution    ***/
/*** and compares it via the chi2 test to the probability mass   ***/
/*** function of another binomial distribution                   ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
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

/********************* chi2_hd() ***********************/
/** For chi^2 test: comparison of histogram to        **/
/** to probabilities:                                 **/
/** Calculates cumulate probability ("p-value") to    **/
/** obtain the corresponding  chi2 value or worse.    **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**  n_bins: number of bins                           **/
/**       h: array of histogram values                **/
/**       p: array of corresp. probabilities          **/
/**                                                   **/
/** Returns:                                          **/
/**       p-value                                     **/
/*******************************************************/
double chi2_hd(int n_bins, int *h, double *p)
{
  int n;                      /* total number of sample points */
  double chi2;                                  /* chi^2 value */
  int K_prime;                  /* number of contributing bins */
  int i;                                            /* counter */

  n = 0;
  for(i=0; i<n_bins; i++)
    n += h[i];      /* calculate total number of sample_points */
  
  chi2 = 0.0; K_prime = 0;
  for(i=0; i<n_bins; i++)                   /* calculate chi^2 */
  {
    if(p[i] > 0)
    {
      chi2 += (h[i]-n*p[i])*(h[i]/(n*p[i])-1.0);
      K_prime ++;
    } 
    else if(h[i] >0)       /* bin entry for zero probability ? */
    {
      chi2 = 1e60;
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
  double p[num_bins];                    /* array of probabilities */

  rng = gsl_rng_alloc(gsl_rng_mt19937);      /* allocate generator */
  gsl_rng_set(rng, 1000);                      /* set seed to 1000 */


  par_n = 10;


  for(par_p=0.05; par_p<0.95; par_p+=0.05)
  { 
    for(i=0; i<num_bins; i++)  /* reset histogram */
    {
      h[i] = 0;
    }

    for(i=0; i<num_r; i++)                     /* generate numbers */
    {
      r = (double) gsl_ran_binomial(rng, par_p, par_n);
      h[(int) r]++;
    }
    for(i=0; i<= par_n; i++)             /* initlize probabilities */
      p[i] = gsl_ran_binomial_pdf(i, 0.5, par_n);

    printf("Q(%f)= %e\n", par_p, chi2_hd(par_n+1, h, p));
  }
  gsl_rng_free(rng);                               /* delete stuff */
  return(0);
}
