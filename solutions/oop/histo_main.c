/*******************************************************************/
/*** Implementation of histograms                                ***/
/*** Main function                                               ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: A sample using C                                   ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "histo.h"

int main(int argc, char *argv[])
{
  histo_t *his;                                       /* histogram */
  int num_bins;                    /* number of bins for histogram */
  double mu;              /* parameter of exponential distribution */
  double number;                                  /* random number */
  int num_runs;              /* amount of generated random numbers */
  int run;                                         /* loop counter */
  int seed;                    /* seed for random number generator */

  mu = 1.0;                                  /* set default values */
  num_bins = 100;
  num_runs = 100000;
  seed = 1000;

  if(argc > 1)
    seed = atoi(argv[1]);             /* read seed from arguments  */
  srand48(seed);

  his = histo_new(0.0, 10*mu, num_bins);

  for(run=0; run<num_runs; run++)       /* generate random numbers */
  {
    number = -log(1-drand48())*mu;    /* use simple srng drand48() */
    histo_insert(his, number);                 /* put in histogram */
  }

#ifndef SOLUTION
  printf("# mean: %f\n", histo_mean(his));         /* show results */
#else
  histo_fprint_pdf(stdout, his);
#endif
  return(0);
}
