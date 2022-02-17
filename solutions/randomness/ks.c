/*******************************************************************/
/*** Generates random numbers for two (different) binomial       ***/
/*** distribution and compares them via the KS test              ***/
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

/************************ Q_ks() ***********************/
/** Probability function for Kolmogorov Smirnov test  **/
/** Implemented accoring "Numerical Recipes in C"     **/
/** Ed. 2, page 626                                   **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**       lambda: argument                            **/
/**                                                   **/
/** Returns:                                          **/
/**       probability                                 **/
/*******************************************************/
double Q_ks(double lambda)
{
  const double eps1 = 0.0001;  /* relative margin for stop */
  const double eps2 = 1e-10;   /* relative margin for stop */
  int i;                                   /* loop counter */
  double sum;                               /* final value */
  double factor;            /* constant factor in exponent */
  double sign;                               /* of summand */
  double term, last_term;        /* summands, last summand */

  sum = 0.0; last_term = 0.0; sign = 1.0;
  factor = -2.0*lambda*lambda;
  for(i=1; i<100; i++)
  {
    term = sign*exp(factor*i*i);
    sum += term;
    if( (fabs(term) <= eps1*fabs(last_term)) || 
	(fabs(term) <= eps2*sum))
      return(2*sum);
    sign =- sign;
    last_term = term;
  }
  return(1.0);     /* in case of no convergence */
}

/************************** ks() ***********************/
/** Kologorov Smirnov test: compare the empirical     **/
/** distribution function to an analytically given    **/
/** distribution function F. Returns p-value =        **/
/** probability that largest differences between the  **/
/** distribution function is as large or larger under **/
/** the null hypothesis that the data was sampled     **/
/** from F.                                           **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**       n: number data points                       **/
/**       x: array of sample points                   **/
/**       F: distribution function                    **/
/**                                                   **/
/** Returns:                                          **/
/**       p-value                                     **/
/*******************************************************/
double ks(int n, double *x, double (*F)(double))
{
  double d, d_max;                    /* (maximum) distance */
  int i;                                    /* loop counter */
  double F_X;            /* empirical distribution function */
  
  qsort(x, n, sizeof(double), compare_double);

  F_X = 0; d_max = 0.0;
  for(i=0; i<n; i++)                    /* scan through F_X */
  {
    d = fabs(F_X-F(x[i]));   /* distance before jump of F_X */
    if( d> d_max)
      d_max = d;
    F_X += 1.0/n;
    d = fabs(F_X-F(x[i]));    /* distance after jump of F_X */
    if( d> d_max)
      d_max = d;
  }
  return(Q_ks( d_max*(sqrt(n)+0.12+0.11/sqrt(n))));
}



/*********************** F_exp() ***********************/
/** Distribution function for exponential distribution**/
/** with parameter lambda=1                           **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**       x: argument                                 **/
/**                                                   **/
/** Returns:                                          **/
/**       F(x)                                        **/
/*******************************************************/
double F_exp(double x)
{
  return(1.0-exp(-x));
}

int main(int argc, char *argv[])
{
  int n;                                     /* sample size */
  double *x;                                      /* sample */
  int i;                                    /* loop counter */
  double mu = 1.0;                /* distribution parameter */

  if(argc !=3 )
  {
    fprintf(stderr, "USAGE %s <n> <mu>\n", argv[0]);
    exit(1);
  }

  n = atoi(argv[1]);                      /* read arguments */
  sscanf(argv[2], "%lf", &mu);

  x = (double *) malloc(n*sizeof(double));
  for(i=0; i<n; i++)                     /* generate sample */
    x[i] = -mu*log(1-drand48());        /* exp. distributed */

  printf("%e\n", ks(n, x, F_exp));

  free(x);
  return(0);
}
