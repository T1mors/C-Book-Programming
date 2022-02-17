/*******************************************************************/
/*** Show how to solve systems of linear equations               ***/
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
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>

int main()
{
  gsl_matrix *A;                                         /* matrix */
  int i, j;                                    /* row/column index */
  gsl_vector *b, *x;                                    /* vectors */
  gsl_permutation *perm;                          /* a permutation */
  int signum;                               /* sign of permutation */

  double values[4*4] = {1.0, 2.5, 3.0, 0.0,                /* data */
                        2.0, 5.0, 1.0, 2.0,
                        3.5, 3.0, 0.0, 3.0,
                        0.0, 2.0, 1.0, 2.0};
  double values2[4] = {15.0, 23.0, 21.5, 15.0};

  A = gsl_matrix_alloc(4,4);            /* allocate and initialize */
  for(i=0; i<4; i++)
    for(j=0; j<4; j++)
      gsl_matrix_set(A, i, j, values[i*4+j]);
  x = gsl_vector_alloc(4);
  b = gsl_vector_alloc(4);
  for(i=0; i<4; i++)
    gsl_vector_set(b, i, values2[i]);
  perm = gsl_permutation_alloc(4);

  gsl_linalg_LU_decomp(A, perm, &signum);        /* solve equation */
  gsl_linalg_LU_solve(A, perm, b, x);

  gsl_vector_fprintf(stdout, x, "%f");

  gsl_matrix_free(A);                               /* free memory */
  gsl_vector_free(b);
  gsl_vector_free(x);
  gsl_permutation_free(perm);
  return(0);
}
  
