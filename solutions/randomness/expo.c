/*******************************************************************/
/*** Function which returns a random number distributed          ***/
/*** according the exponential distribution                      ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Inversion method                                   ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 100
/********************* rand_expo() ********************/
/** Returns random number which is exponentially     **/
/** distributed                                      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       mu: parameter of distribution              **/
/** RETURNS:                                         **/
/**     random number                                **/
/******************************************************/
double rand_expo(double mu)
{
  double randnum;                  /* random number U(0,1) */
  randnum = drand48();

  return(-mu*log(1-randnum));
}


int main(int argc, char *argv[])
{
  int histo[NUM_BINS];                                    /* histogram */
  int bin;
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int t;                                               /* loop counter */
  int num_runs;                  /* number of generated random numbers */
  double mu;                              /* parameter of distribution */
  double number;                                   /* generated number */
  double threshold = 0;            /* lower limit of generated numbers */
  double p;                            /* probability for entry in bin */


  if(argc < 3)                           /* check number of arguments */
  {
    fprintf(stderr, "USAGE %s <num_runs> <mu> [<threshold>]\n", argv[0]);
    exit(1);
  }

  num_runs = atoi(argv[1]);                         /* read parameters */
  sscanf(argv[2], "%lf", &mu);
  if(argc > 3)   /* optional 3rd parameter ? */
    sscanf(argv[3], "%lf", &threshold);


  for(t=0; t<NUM_BINS; t++)                    /* initialise histogram */
      histo[t] = 0;
  start_histo = 0.0; end_histo = 10.0*mu;
  delta = (end_histo - start_histo)/NUM_BINS;

  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    do
      number = rand_expo(mu);            /* generate exp-distr. number */
    while(number < threshold);              /* accept only > threshold */
    bin = (int) floor((number-start_histo)/delta);
    if( (bin >= 0)&&(bin < NUM_BINS))                /* inside range ? */
       histo[bin]++;                                    /* count event */
  }

  for(t=0; t<NUM_BINS; t++)              /* print normalized histogram */
  {                                      /* including error bars */
    p = (double) histo[t]/num_runs;
    if(p>0)
      printf("%f %f %f\n", start_histo + (t+0.5)*delta,
             p/delta, sqrt(p*(1-p)/num_runs)/delta);
  }

  return(0);
}

