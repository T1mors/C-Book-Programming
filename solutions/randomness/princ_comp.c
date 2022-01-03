/*******************************************************************/
/*** Principal component analysis of a set of vectors            ***/
/*** COMPILE:                                                    ***/
/*** cc -o princ_comp princ_comp.c -lgsl -lgslcblas -lm -Wall    ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
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
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>


/************** principal_components() *****************/
/** Calculates covariance matrix of 'data' points     **/
/** and obtaines eigenvalus and eigenvectors in       **/
/** descending order (=principal component analysis   **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**     (*) eval: eigen values                        **/
/**    (*) evec: eigen vectors (columns of matrix)    **/
/**        data: data vectors (columns of matrix)     **/
/**                                                   **/
/** Returns:                                          **/
/**        (nothing)                                  **/
/*******************************************************/
void principal_components(gsl_vector *eval, gsl_matrix *evec,
			  gsl_matrix *data)
{
  int t,d1, d2;                                   /* loop counters */
  int dim;           /* number of components of data point vectors */
  int num_points;                         /* number of data points */
  gsl_matrix *cov;                            /* covariance matrix */
  gsl_vector *avg;                                     /* averages */
  gsl_eigen_symmv_workspace *w;      /* memory for eigenvalues etc */
  num_points = data->size2;                          /* initialize */
  dim = data->size1;
  avg = gsl_vector_alloc(dim);
  cov = gsl_matrix_alloc(dim, dim);
  
  for(d1=0; d1<dim; d1++)                   /* calculated averages */
  {
    gsl_vector_set(avg, d1, 0);
    for(t=0; t<num_points; t++)
      gsl_vector_set(avg, d1, gsl_vector_get(avg, d1)
		             +gsl_matrix_get(data, d1, t));
  }  
  gsl_vector_scale(avg, 1.0/ num_points);

  for(d1=0; d1<dim; d1++)           /* calculate covariance matrix */
    for(d2=d1; d2<dim; d2++)
    {
      gsl_matrix_set(cov, d1, d2, 
	       -gsl_vector_get(avg, d1)*gsl_vector_get(avg, d2));
      for(t=0; t<num_points; t++)
	gsl_matrix_set(cov, d1, d2, gsl_matrix_get(cov, d1, d2)+   
		       gsl_matrix_get(data, d1, t)
		       *gsl_matrix_get(data, d2, t)/num_points);
      gsl_matrix_set(cov, d2, d1, gsl_matrix_get(cov, d1, d2));
    }
 

  w = gsl_eigen_symmv_alloc(dim); /* calculate eigenvectors/values */
  gsl_eigen_symmv(cov, eval, evec, w);

  for(t=0; t<dim; t++) /* order eigenvalues (and corresp. vectors) */
    for(d1=0; d1<dim-1; d1++)
      if(gsl_vector_get(eval, d1) < gsl_vector_get(eval, d1+1))
      {
	gsl_matrix_swap_columns(evec, d1, d1+1);
	gsl_vector_swap_elements(eval, d1, d1+1);
      }

  gsl_eigen_symmv_free(w);
  gsl_vector_free(avg);
  gsl_matrix_free(cov);
}

/***************** generate_data() *********************/
/** Generate 'num_points' vectors of random data      **/
/** each vector has 'dim' components                  **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**         dim: size of vectors                      **/
/**  num_points: number of vectors                    **/
/**                                                   **/
/** Returns:                                          **/
/**    matrix containing the vectors (=columns)       **/
/*******************************************************/
gsl_matrix *generate_data(int dim, int num_points)
{
  gsl_matrix *data;          /* matrix containing random vectors */
  int t, d;                                     /* loop counters */
  gsl_rng *r;                         /* random number generator */
  double randnum;                      /* Gaussian random number */
  int do_print = 1;                             /* print vectors */

  data = gsl_matrix_alloc(dim, num_points);
  r = gsl_rng_alloc(gsl_rng_mt19937);

  for(t=0; t<num_points; t++)                 /* generate points */
  {
    randnum = gsl_ran_gaussian(r, 1.0);       /* first component */
    for(d=0; d<dim; d++)
      gsl_matrix_set(data, d, t, 2.0*randnum);
    randnum = gsl_ran_gaussian(r, 1.0);      /* second component */
    for(d=0; d<dim; d++)
      gsl_matrix_set(data, d, t,
     	     gsl_matrix_get(data, d, t)+(1-d)*randnum/(d+1)  );
  }

  if(do_print)
    for(t=0; t<num_points; t++)               /* generate points */
    {
      for(d=0; d<dim; d++)
	printf("%f ", gsl_matrix_get(data, d, t));
      printf("\n");
    }


  gsl_rng_free(r);

  return(data);
}

/********************** main program               *********************/
int main(int argc, char *argv[])
{
  int dim = 3;  /* number of components of random vectors */
  int t, d;  /* loop counters */
  int num_points; /* number of vectors */
  gsl_matrix *data;    /* random vectors, row by row */
  gsl_vector *eval;   /* eigenvalues */
  gsl_matrix *evec;   /* eigenvectors */

  num_points = 200;
  data = generate_data(dim, num_points);
  eval = gsl_vector_alloc(dim);
  evec = gsl_matrix_alloc(dim, dim);
  principal_components(eval, evec, data);

  for(t=0; t<dim; t++)   /* show eigenvalues/vectors */
  {
    printf("# eval: %f (", gsl_vector_get(eval, t));
    for(d=0; d<dim; d++)
      printf("%f, ", gsl_matrix_get(evec, d, t));
    printf(")\n");
  }


  gsl_matrix_free(data);
  return(0);

}
