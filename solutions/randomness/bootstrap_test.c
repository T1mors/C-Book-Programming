/*******************************************************************/
/*** Test the boostrap method for the mean, for number generated ***/
/*** from exponential distribution                               ***/
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

int main(int argc, char *argv[])
{
  double mu;                          /* parameter of distribution */
  double sigma;                       /* parameter of distribution */
  double gamma;                       /* parameter of distribution */
  double E;                                   /* expectation value */
  double *x;                                      /* sample points */
  int num_runs;              /* amount of generated random numbers */
  int run;                                         /* loop counter */
  int seed, seed0, num_seeds; /* seeds for random number generator */
  int bs_runs;                  /* number of resampling iterations */
#ifdef SOLUTION
  double low, high;               /* bootstrap confidence interval */
#endif
  double alpha;                              /* significance level */
  double s_mean;                                    /* sample mean */
  double error_bar;        /* <-> standard Gaussian conf. interval */
  double error_bar2;      /* <-> standard bootstrap conf. interval */
  int inside_std;   /* counter how often confidence interval is OK */
  int inside_bs;    /* counter how often confidence interval is OK */
  int do_print;          /* print confidence intervals to screen ? */

  mu = 1.0;                                  /* set default values */
  sigma = 1.0;
  gamma = 1.5;
  num_runs = 100;
  seed0 = 1000; num_seeds = 1000;
  bs_runs = 1000;
  alpha = 0.32;
  do_print = 1;


  x = (double *) malloc(num_runs*sizeof(double));

  inside_std = 0; inside_bs = 0;
  E = gamma/(gamma-1);                  /* assign expectation value */
  for(seed=seed0; seed<seed0+num_seeds; seed++)
  {
    srand48(seed);
    run = 0;
    while(run < num_runs)                /* generate random numbers */
    {
      /*x[run++] = -log(1-drand48())*mu;*/  /* use simple drand48() */
      x[run++] = pow(1-drand48(),-1/gamma);
    }

    /** do analysis **/
    s_mean =  mean(num_runs, x);  /* calculate mean/conf. intervals */
    error_bar =  sqrt(variance(num_runs, x)/(num_runs-1));
    if(fabs(E-s_mean)<error_bar)       /* is true expectation value */
      inside_std++;                 /* inside confidence interval ? */
#ifdef SOLUTION    
    bootstrap_ci(num_runs, x, bs_runs, alpha, mean, &low, &high);
    if( (low<E)&&(E<high) )            /* is true expectation value */
      inside_bs++;                  /* inside confidence interval ? */
#else
    error_bar2 = bootstrap_variance(num_runs, x, bs_runs, mean);
    if(fabs(E-s_mean)<error_bar2)      /* is true expectation value */
      inside_bs++;                 /* inside confidence interval ? */
#endif
				    if(do_print)
    {
      printf("# mean: %f\n", s_mean);
      printf("# standard  confidence interval: [%f,%f],\n", 
	     s_mean-error_bar, s_mean+error_bar);
#ifdef SOLUTION
      printf("# bootstrap confidence interval: [%f,%f],\n", low, high);
#else
      printf("# bootstrap confidence interval: [%f,%f],\n", 
	     s_mean-error_bar2, s_mean+error_bar2);
#endif
    }
  }  

    
  printf("# True expect. value mu=%f inside confidence interval:\n", 
	 E);
  printf("# For standard Gaussian confidence interval: %f \n", 
	 (double) inside_std/num_seeds);
  printf("# For bootstrap confidence interval: %f \n", 
	 (double) inside_bs/num_seeds);
  free(x); 

  return(0);
}

