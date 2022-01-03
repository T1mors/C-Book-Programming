/*******************************************************************/
/*** Use maximum likelihood approach to determine parameters     ***/
/*** of a Fisher-Tippett distribution that fit best data 
/*** generated according the Fischer-Tippett distribution        ***/
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

#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

/** structure to hold a sample **/
typedef struct
{
  int       n;       /* number of sample points; */
  double   *x;                         /* sample */
}
sample_t;

double rand_fisher_tippett(double lambda);

/************************ ll_ft() *********************/
/** -Log likelihood function for Fisher-Tippett      **/
/** distribution                                     **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       par: parameters of distribution            **/
/**            (=arguments of fct to be minimized    **/
/**      data: size of sample + sample               **/
/** RETURNS:                                         **/
/**     random number                                **/
/******************************************************/
double ll_ft(const gsl_vector *par, void *param)
{
  double lambda, x0;                     /* parameters of pdf */
  sample_t *sample;                                 /* sample */
  double sum;          /* sum of log-likelihood contributions */
  int i;                                      /* loop counter */

  lambda = gsl_vector_get(par, 0);                /* get data */ 
  x0 = gsl_vector_get(par, 1); 
  sample = (sample_t *) param;

  sum = sample->n*log(lambda);    /* calculate log likelihood */
  for(i=0; i<sample->n; i++)
    sum -= lambda*(sample->x[i]-x0) + 
           exp(-lambda*(sample->x[i]-x0));

  return(-sum);                    /* return - log likelihood */
}

int main(int argc, char *argv[])
{
  double lambda, x0;    /* initial parameters of distribution */
  int num_par;                        /* number of parameters */
  sample_t sample;                                  /* sample */
  int i, iter;                                     /* counter */
  int status;                          /* status of iteration */
  double size;                             /* size of simplex */

  gsl_multimin_fminimizer *s;           /* the full mimimizer */
  gsl_vector *simplex_size;        /* (relative) simplex size */ 
  gsl_vector *par; /* params to be optimized = args of target */
  gsl_multimin_function f;  /* holds function to be optimized */
  


  sample.n = 10000;                          /* initilization */
  sample.x = (double *) malloc(sample.n*sizeof(double));
  lambda = 3.0;
  x0 = 2.0;
  num_par = 2;
  if(argc > 1)
    srand48(atoi(argv[1]));    /* seed according 1st argument */

  for(i=0; i<sample.n; i++)     /* generate F-T distr. sample */
    sample.x[i] += x0+rand_fisher_tippett(lambda); 

  f.f = &ll_ft;                    /* initialize minimization */
  f.n = num_par;
  f.params = &sample;
  simplex_size = gsl_vector_alloc(num_par);  /* alloc simplex */
  gsl_vector_set_all(simplex_size, 1.0);      /* init simplex */
  par = gsl_vector_alloc(num_par);  /* alloc + init arguments */
  gsl_vector_set(par, 0, 1.0);
  gsl_vector_set(par, 1, 1.0);
  s =
    gsl_multimin_fminimizer_alloc(gsl_multimin_fminimizer_nmsimplex, 
				  num_par);
  gsl_multimin_fminimizer_set(s, &f, par, simplex_size);

  do                                  /* perform minimization */
  {
    iter++;
    status = gsl_multimin_fminimizer_iterate(s);  /* one step */
    if(status)    /* error ? */ 
      break;
    size = gsl_multimin_fminimizer_size(s);    /* converged ? */
    status = gsl_multimin_test_size(size, 1e-4);
  }
  while( (status == GSL_CONTINUE) && (iter<100) );
    
  printf("%d -> (%f,%f) (size=%f)\n", iter,
	 gsl_vector_get(s->x, 0),gsl_vector_get(s->x, 1), size);

  gsl_vector_free(par);                    /* free everything */
  gsl_vector_free(simplex_size);
  gsl_multimin_fminimizer_free(s);
  free(sample.x);
  return(0);
}

