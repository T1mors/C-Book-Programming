/*******************************************************************/
/*** Function which generates random points uniformly            ***/
/*** distributed inside or on a sphere.                          ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A comprehensive practical guide to computer simulation      ***/
/*** World Scientific, Singapore 2014                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Rejection Method                                   ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/******************* generate_sphere *****************/
/** Generates a random 'dim' dimensional 'point'    **/
/*+ which is uniformly distributed in the unit      **/
/** 'dim'-dimensional sphere (centered at 0)        **/
/** if 'surface' only points on the surface of the  **/
/** sphere are generated                            **/
/** Uses rejection method.                          **/
/** PARAMETERS: (*)= return-paramter                **/
/**       dim: dimension of system                  **/
/** (*) point: generated vector                     **/
/**   surface: project on surface of sphere ?       **/
/** RETURNS:                                        **/
/**  number of trails needed                        **/
/*****************************************************/
int generate_sphere(int dim, double *x, int surface)
{
  int num_trials;
  int d;
  double magnitude;          /* square magnitude of vector */
  
  num_trials = 0;
  do 
  {
    num_trials++;
    magnitude = 0;
    for(d=0; d<dim; d++)    /* generate point in [0,1]^dim */
    {
      x[d] = 2*drand48()-1.0;
      magnitude += x[d]*x[d];
    }  
  } while(magnitude > 1.0);      /* until in unit sphere ? */

  magnitude = sqrt(magnitude);
  if(surface)      
    for(d=0; d<dim; d++)    /* normalize point to length 1 */
      x[d] /= magnitude;
  return(num_trials);
}

int main(int argc, char **argv)
{
  int t, d;
  int dim;
  dim = 2;
  double point[dim];
  int num_trials, num_runs = 1000;
  double prob;

  if(argc > 1)
    num_runs = atoi(argv[1]);
  num_trials = 0;
  for(t=0; t<num_runs; t++)
  {
    num_trials += generate_sphere(dim, point, 1);
    for(d=0; d<dim; d++)
      printf("%f ", point[d]);
    printf("\n");
  }
  prob = (double) num_runs/num_trials;
  printf("# %d %d %f\n", num_runs, num_trials, prob);
  
  return(0);
}
