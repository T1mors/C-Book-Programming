/*******************************************************************/
/*** Program for calculating the potential for a two-dimensional ***/
/*** charge distribution                                         ***/
/***                                                             ***/
/*** Lecture: Computational Physics                              ***/
/*** A.K. Hartmann 2011                                          ***/
/***                                                             ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calc_potential(int dim, int num, double *q, double r[num][dim], double *x)
{
  double potential = 0.0;
  for (int i = 0; i < num; i++)
  {
    double distance = 0.0;
    for (int j = 0; j < dim; j++)
    {
      distance += (r[i][j] - x[j]) * (r[i][j] - x[j]);
    }
    distance = sqrt(distance);
    if (distance == 0.0)
    {
      potential = 1000000000;
    }
    else
    {
      potential += q[i] / distance;
    }
  }

  return potential;
}

/***************** main program *********************************/
int main(int argc, char **argv)
{
  int num_charges = 2;          /* number of charges */
  int dim = 2;                  /* dimensionality of system */
  double q[num_charges];        /* value of charges */
  double pos[num_charges][dim]; /* position of charges */
  int c;                        /* counters */
  double potential;             /* for summing up potential */
  double dr;                    /* difference (in a certain direction) */
  double r, r2;                 /* absolute value of difference vector, squared */
  int d;
  double obs_pos[dim]; /* dimension counter */

  /** setup charges **/
  q[0] = 1;
  pos[0][0] = -1.025;
  pos[0][1] = 0;
  q[1] = -1;
  pos[1][0] = 1.025;
  pos[1][1] = 0;

  /* example for setting position */
  /** iterate over some positions **/
  /** COMPLETE THE MAIN PROGRAM HERE:                        **/
  /** ITERATE SUITABLY x[0],x[1] AND OUTPUT EACH TIME x[0] x[1] V(x)   **/
  dr = 0.05;
  for (double x = -2; x < 2; x += dr)
  {
    for (double y = -2; y < 2; y += dr)
    {
      obs_pos[0] = x;
      obs_pos[1] = y;

      potential = calc_potential(dim, num_charges, q, pos, obs_pos);
      printf("%f %f %f\n", x, y, potential);
    }
  }

  return (0);
}
