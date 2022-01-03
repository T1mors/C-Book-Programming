/*******************************************************************/
/*** Draw random number for the Gaussian distribution using      ***/
/*** the rejection method. The exponential function is used to   ***/
/*** border the Gaussian.  A histogram is recored                ***/
/***                                                             ***/
/*** Solution to exercise from the book:                         ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Exercises                                          ***/
/*******************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*#define drand48() ((double) rand()/RAND_MAX)*/

#define NUM_BINS 280

/**************** reject_gaussian() *******************/
/** Generates Gaussian distributed random number     **/
/** using the rejection method via bordering the     **/
/** positive part of the Gaussian by exp(-x). With   **/
/** probability 1/2 the sign is negated.             **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       none                                       **/
/** RETURNS:                                         **/
/**     random number                                **/
/******************************************************/
double reject_gaussian()
{
  int found;               /* flag if valid number has been found */
  double x,y;               /* random points in [x0,x1]x[0,p_max] */
  found = 0;
  while(!found)                 /* loop until number is generated */
  {
    x = -log(1-drand48()); /* exp. random number via inversion method  */
         /** SQRT(2*PI) omitted in generation of y and in test y<p(x) **/
    y = exp(0.5-x)*drand48();           /* uniformly in [0,exp(0.5-x)] */
    if(y <= exp(-x*x/2))                                   /* accept ? */
	found = 1;
  }
  if(drand48()<0.5)
    return(x);
  else 
    return(-x);
}




int main(int argc, char *argv[])
{
  int histo[NUM_BINS];                       /* poor mans histogram */
  int bin;
  double start_histo, end_histo;              /* range of histogram */
  double delta;                                     /* width of bin */
  int t;                                            /* loop counter */
  int num_runs;               /* number of generated random numbers */     
  double number;                                /* generated number */

  num_runs = 10000;                                /* default value */

  if(argc > 1)
    num_runs = atoi(argv[1]);                    /* read parameters */

  for(t=0; t<NUM_BINS; t++)                 /* initialise histogram */
      histo[t] = 0;        
  start_histo = -7; end_histo = 7;
  delta = (end_histo - start_histo)/NUM_BINS; 
  
  for(t=0; t<num_runs; t++)                            /* main loop */
  {
    number = reject_gaussian();                  /* generate number */
    bin = (int) floor((number-start_histo)/delta);
    if( (bin >= 0)&&(bin < NUM_BINS))             /* inside range ? */
       histo[bin]++;                                 /* count event */
  }

  for(t=0; t<NUM_BINS; t++)           /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*num_runs));

  return(0);
}
