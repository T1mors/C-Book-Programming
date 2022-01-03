/*******************************************************************/
/*** Prints binomial distribution Bin(n,p)                       ***/
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
#include <gsl/gsl_randist.h>

int main(int argc, char *argv[])
{
  int n;                             /* parameters of distribution */
  double p; 
  int x;                                        /* argument of pdf */ 
  double prob;                            /* resulting probability */
  int argz = 1;             /* for treating command line arguments */

  sscanf(argv[argz++], "%lf", &p);
  n = atoi(argv[argz++]);                         /* get arguments */

  for(x=0; x<=n; x++)        /* iterate to print full distribution */
  {
    prob = gsl_ran_binomial_pdf(x, p, n);
    printf("%d %f\n", x, prob);
  }
  return(0);
}
