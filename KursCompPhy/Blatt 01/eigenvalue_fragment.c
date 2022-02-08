/*******************************************************************/
/*** Generates random matrices an determines maximum eigenvalue  ***/
/*** via sequence of multiplications                             ***/
/***                                                             ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void normalize(double *vec, int len_vec);

// TODO Use command line arguments to differ between print_matrix and print_hist

int main()
{
  int n = 3;                   /* matrix has size n x n */
  double matrix[n][n];         /* random matrix */
  double vec[n], vec2[n];      /* vectors */
  double norm;                 /* length of vector */
  int i, j, k, mat;            /* loop counters for rows, columns */
  int seed;                    /* of RNG */
  int iter, max_iter;          /* loop counter for eigenvalue iteration */
  double mu;                   /* estimator for larges eigenvalue */
  int num_bins = 200, bin;     /* size of histogram, bin */
  double histo[num_bins];      /* histogram */
  double histo_from, histo_to; /* range of histogram */
  double delta;                /* size of one bin */

  histo_from = -10, histo_to = 10; /* initialize histogram */
  delta = (histo_to - histo_from) / num_bins;
  for (k = 0; k < num_bins; k++)
    histo[k] = 0;

  seed = 1000;
  srand48(seed);

  /** INSERT LOOP FOR TREATING MANY MATRICES HERE **/
  int num_matrices = 100000;
  bool print_matrix = false;
  bool print_hist = true;
  for (mat = 0; mat < num_matrices; mat++)
  {

    for (i = 0; i < n; i++) /* initialize matrix */
    {
      matrix[i][i] = 1.0;
      for (j = 0; j < i; j++)
      {
        matrix[i][j] = 2 * drand48() - 1;
        matrix[j][i] = matrix[i][j];
      }
    }
    for (i = 0; i < n; i++) /* initialize vector */
      vec[i] = 2 * drand48() - 1;

    // // Easy Matrices
    // matrix[0][0] = 1;
    // matrix[0][1] = 2;
    // matrix[1][0] = 2;
    // matrix[1][1] = 1;

    // // Starting Vec
    // // This can result in a vector that faces the exact opposite direction vec -> -vec
    // vec[0] = 2;
    // vec[1] = 3;

    // Print out matrix itself
    if (print_matrix)
    {
      printf("# Matrix:\n");
      for (i = 0; i < n; i++)
      {
        printf("# ");
        for (j = 0; j < n; j++)
        {
          printf("%f\t", matrix[i][j]);
        }
        printf("\n");
      }
      printf("\n");
      printf("# iter norm vec2[0]/vec1[0], mu\n");
    }
    max_iter = 40;

    for (iter = 0; iter < max_iter; iter++) /* find largest eigenvalue */
    {

      norm = 0.0; /* normalize vector */
      /** PLEASE INERT CODE TO NORMALIZE vec[] HERE **/
      normalize(vec, n);

      /** PLEASERT INSERT CODE To CALCULATE vec2 = matrix x vec **/
      for (i = 0; i < n; i++)
      {
        vec2[i] = 0;
        for (j = 0; j < n; j++)
        {
          vec2[i] += matrix[i][j] * vec[j];
        }
      }

      mu = 0; /* determine estimator for eigenvalue */
      for (i = 0; i < n; i++)
        mu += vec[i] * vec2[i];
      if (print_matrix)
        printf("%d %f %f %f\n", iter, norm, vec2[0] / vec[0], mu);

      for (i = 0; i < n; i++)
        vec[i] = vec2[i];
    }

    // Endresult for Eigenvector and Eigenvalue
    if (print_matrix)
    {
      printf("\n# Eigenvalue: %lf to Eigenvector: ", mu);
      // Normalize again
      normalize(vec, n);
      for (i = 0; i < n; i++)
      {
        printf("%lf ", vec[i]);
      }
      printf("\n");
    }

    bin = (int)floor((mu - histo_from) / delta); /* update histogram */
    if ((bin >= 0) && (bin < num_bins))
      histo[bin]++;
  }
  if (print_hist)
  {
    for (k = 0; k < num_bins; k++)
      printf("%f %f\n", histo_from + (k + 0.5) * delta, histo[k]);
  }
  return (0);
}

// Input: pointer to vector and length of vector
void normalize(double *vec, int len_vec)
{
  double norm = 0.0;
  for (int i = 0; i < len_vec; i++)
  {
    norm += vec[i] * vec[i];
  }
  norm = sqrt(norm);
  for (int i = 0; i < len_vec; i++)
  {
    vec[i] /= vec[i] / norm;
  }
}