/*******************************************************************/
/*** Sample a discrete distribution function from a table.       ***/
/*** Here: Poisson distribution (solution to exercise)           ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: exercises                                          ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/********************* init_poisson() *****************/
/** Generates  array with distribution function      **/
/** for Poisson distribution with mean mu:           **/
/** F(k)=mu^k*exp(-mu)/x!                            **/
/** The size of the array is automatically adjusted. **/
/** PARAMETERS: (*)= return-paramter                 **/
/**   (*) n_p: p. to number of entries in table      **/
/**        mu: parameter of distribution             **/
/** RETURNS:                                         **/
/**     pointer to array with distribution function  **/
/******************************************************/
double *init_poisson(int *n_p, double mu)
{
  int k;                                     /* entry counter */
  int n;                         /* maximum number of entries */
  double prob, sum;                       /* probability, sum */
  double *F;               /* array for distribution function */
  n = 5;

  F = (double *)malloc(n*sizeof(double));   /* allocate array */
  prob = exp(-mu);                              /* initialize */
  sum = 0;
  k = 0;
  while(prob > 0)                               /* fill array */
  {
    sum += prob;
    if(k==n)                        /* end of array reached ? */
    {
	n *=2;                                 /* double size */
	F = realloc(F, n*sizeof(double));
    }
    F[k] = sum;
    k++;
    prob *= mu/k;
  }
  while(k<n)                         /* fill till end of array */
      F[k++] = 1.0;

  *n_p = n;
  return(F);
}

/******************** rand_discrete() *****************/
/** Returns natural random number distributed        **/
/** according a discrete distribution given by the   **/
/** distribution function in array 'F'               **/
/** Uses search in array to generate number          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       n: number of entries in array              **/
/**       F: array with distribution function        **/ 
/** RETURNS:                                         **/
/**     random number                                **/
/******************************************************/
int rand_discrete(int n, double *F)
{
  double randnum;                /* random number U(0,1) */
  int x;                /* integer number to be returned */

  randnum = drand48();
  x = 0;
  while(F[x] < randnum)          /* search through table */  
      x++;
  return(x);
}


int main(int argc, char *argv[])
{
  double mu;                                         /* parameter */
  int num_entries;            /* number of tables in distribution */
  double *F;                             /* distribution function */
  int n_measure = 10000;                /* number of measurements */
  double sum;                               /* measurement points */
  int i;                                               /* counter */
  
  mu = 3.0;
  F = init_poisson(&num_entries, mu);        /* init distribution */

  if(argc > 1)
    srand48(atoi(argv[1]));       /* set seed according first arg */

  sum = 0.0;       /* genererate number according discrete distr. */
  for(i=0; i<n_measure; i++)  
    sum += (double) rand_discrete(num_entries, F); 

  printf("# expectation value: %f mean: %f\n", 
	 mu, sum/n_measure);                      /* print result */
  free(F);                                            /* clean up */
  return(0);
}

