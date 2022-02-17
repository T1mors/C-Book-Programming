/*******************************************************************/
/*** Function which returns a random number distributed          ***/
/*** according the Fischer-Tippett distribution                  ***/
/*** A histogram of the data is recorded.                        ***/
/***                                                             ***/
/*** Solution of a problem from the book:                        ***/
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

/*#define drand48() ((double) rand()/RAND_MAX)*/

#define NUM_BINS 50

/******************** rand_fisher_tippett() ***********/
/** Returns random number which is distributed       **/
/** according the Fisher-Tippett distribution        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       lambda: parameter of distribution          **/
/** RETURNS:                                         **/
/**     random number                                **/
/******************************************************/
double rand_fisher_tippett(double lambda)
{
  double u;                            /* random number U(0,1) 0<=1<1 */
  u = drand48();

  return(-log(-log(1.0-u))/lambda);    /* 1-u is also U(0,1) but >0 ! */
}


int main(int argc, char *argv[])
{
  double lambda, x0;                     /* parameter of distribution */
  int n=1000000;                              /* number of measurements */
  int t;                                                   /* counter */
  int histo[NUM_BINS];                         /* poor mans histogram */
  int bin;
  double start_histo, end_histo;                /* range of histogram */
  double delta;                                       /* width of bin */
  double number;                                  /* generated number */
   
  lambda = 3.0;
  x0 = 2.0;

  if(argc > 1)
    srand48(atoi(argv[1]));      /* set seed according first argument */

  for(t=0; t<NUM_BINS; t++)                   /* initialise histogram */
      histo[t] = 0;        
  start_histo = x0-lambda; end_histo = x0+4*lambda;
  delta = (end_histo - start_histo)/NUM_BINS; 

  for(t=0; t<n; t++)
  {
    number = x0+rand_fisher_tippett(lambda); /* gen.F-T distr. number */
    /*printf("%f\n", number);*/
    bin = (int) floor((number-start_histo)/delta);
    if( (bin >= 0)&&(bin < NUM_BINS))               /* inside range ? */
       histo[bin]++;                                   /* count event */
  }

  for(t=0; t<NUM_BINS; t++)             /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*n));

  return(0);
}
