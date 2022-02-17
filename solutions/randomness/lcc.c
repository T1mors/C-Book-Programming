/*******************************************************************/
/*** Linear Correlation Coefficient. Tested via:                 ***/
/*** Generates pairs of random numbers, the first number         ***/
/*** according a standard Gaussian distribution and  the second  ***/
/*** according a Gaussian where the mean is proportional to the  ***/
/*** first number.                                               ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
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

/**************************** lcc() ********************/
/** Calculates the linear correlation coefficient     **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**     n: number of data points                      **/
/**     x: first element of sample set                **/
/**     y: second element of sample set               **/
/**                                                   **/
/** Returns:                                          **/
/**       r                                           **/
/*******************************************************/
double lcc(int n, double *x, double *y)
{
  double r;                /* linear correlation coefficient */
  double x_mean, y_mean;                     /* sample means */
  double x_var, y_var;                   /* sample variances */
  int i;                                     /* loop counter */

  x_mean = 0.0; y_mean = 0.0;      /* calculate sample means */
  for(i=0; i<n; i++)
  {
    x_mean += x[i];
    y_mean += y[i];
  }
  x_mean /= n; y_mean /= n;

  x_var = 0.0; y_var = 0.0;   /* calculate sample variances */
  for(i=0; i<n; i++)
  {
    x_var += (x[i]-x_mean)*(x[i]-x_mean);
    y_var += (y[i]-y_mean)*(y[i]-y_mean);
  }
  

  r = 0.0;  /* calculate linear correlation coefficient */
  for(i=0; i<n; i++)
    r += (x[i]-x_mean)*(y[i]-y_mean);
  r /= sqrt(x_var*y_var);

  return(r);
}


int main(int argc, char *argv[])
{
  int n;                                 /* number of sample points */
  int i;                                           /* loop counters */
  double u1, u2;                           /* U(0,1) random numbers */
  double r1, r2;                  /* standard normal random numbers */
  double *x, *y;                            /* final random numbers */
  double kappa;                          /* strength of correlation */
  int print_points;                                        /* flags */


  print_points = 0;

  kappa = 0.0;                   /* read arguments/ standard values */
  if(argc > 1)
    sscanf(argv[1], "%lf", &kappa);
  n = 10000;
  if(argc > 2)
    n = atoi(argv[2]);

  x = (double *) malloc(n*sizeof(double));              /* allocate */
  y = (double *) malloc(n*sizeof(double));

  for(i=0; i<n; i++)                         /* perform experiments */
  {
    u1 = drand48();              /* generate Gaussian distr. number */
    u2 = drand48();
    r1 = sqrt(-2.0*log(1-u1))*sin(2*M_PI*u2);
    r2 = sqrt(-2.0*log(1-u1))*cos(2*M_PI*u2);
    x[i] = r1;
    y[i] = kappa*r1+r2;               /* generate correlated number */
    if(print_points)
      printf("%f %f\n", x[i], y[i]);
  }

  printf("# r: %e\n", lcc(n, x, y));

  free(x);
  free(y);

  return(0);
}
