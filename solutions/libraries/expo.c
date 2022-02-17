/*******************************************************************/
/*** Generates random numbers according exponential distribution ***/
/*** and puts them into histogram with logarithmic binning       ***/
/***                                                             ***/
/*** Solutuion to exercise from the book:                        ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Libraries                                          ***/
/*** Section: gnu scientific library                             ***/
/*******************************************************************/

#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_histogram.h>

/************** print_norm_histogram() *****************/
/** Prints histogram as probability density function. **/
/** For each bin [l,u) its mid point                  **/
/** (l+u)/2 and its count normalized by the           **/
/** total count and by the bin width (u-l)            **/
/** is shown.                                         **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**       h: histogram                                **/
/*                                                    **/
/** Returns:                                          **/
/**       (nothing)                                   **/
/*******************************************************/
void print_norm_histogram(gsl_histogram *h)
{
  double sum;                          /* of all histogram entries */
  size_t num_bins;                  /* number of bins in histogram */
  size_t i;                                    /* bin loop counter */
  double lower, upper;                           /* range of a bin */
  num_bins = gsl_histogram_bins(h);
  
  sum = 0;                              /* calculate normalization */
  for(i=0; i<num_bins; i++)
    if(gsl_histogram_get(h, i) > 0)
      sum += gsl_histogram_get(h, i); 

  for(i=0; i<num_bins; i++)              /* print histogram as pdf */
  {
    gsl_histogram_get_range(h, i, &lower, &upper);
    if(gsl_histogram_get(h, i) > 0)
      printf("%e %e\n", (lower+upper)/2.0, 
	     gsl_histogram_get(h, i)/(sum*(upper-lower)));
  }

}


int main()
{
  gsl_rng *rng;            /* pointer to a random number generator */
  int n = 1000000;                     /* number of random numbers */
  int i;                                           /* loop counter */
  double r;                                     /* a random number */
  gsl_histogram *histo;               /* histogram to store result */
  int num_bins = 30;                /* number of bins of histogram */
  double range[num_bins+1];
  double x0;                                /* for setting up bins */
  double f;                      /* factor for logarithmic binning */

  rng = gsl_rng_alloc(gsl_rng_mt19937);      /* allocate generator */
  gsl_rng_set(rng, 1000);                      /* set seed to 1000 */

  histo = gsl_histogram_alloc(num_bins);
  x0 = 0.1;
  f = 1.2;
  range[0] = 0.0;
  for(i=1; i<=num_bins; i++)
  {
    range[i] = x0;
    x0 *= f;
  }
  gsl_histogram_set_ranges(histo, range, num_bins+1);

  for(i=0; i<n; i++)                           /* generate numbers */
  {
    r = gsl_ran_exponential(rng, 2.0);
    gsl_histogram_increment(histo, r);
  }

  print_norm_histogram(histo);
  /* gsl_histogram_fprintf(stdout, histo, "%f", "%f");*/

  gsl_rng_free(rng);                               /* delete stuff */
  gsl_histogram_free(histo);
  return(0);
}
