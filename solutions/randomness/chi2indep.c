/*******************************************************************/
/*** Chi-squared test for pairs of numbers. Tested via:          ***/
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
#include <gsl/gsl_cdf.h>

/********************* chi2_indep() ********************/
/** chi^2 test for independence of pairs (x,y) of     **/
/** data: comparison of two-dimensional histogram to  **/
/** corresponding histogram obtained under the        **/
/** assumption of independence.                       **/
/** Calculates cumulate probability ("p-value") to    **/
/** obtain the corresponding  chi2 value or worse.    **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**     n_x: number of bins in x-direction            **/
/**     n_y: number of bins in y-direction            **/
/**       h: 2d array of histogram values             **/
/**                                                   **/
/** Returns:                                          **/
/**       p-value                                     **/
/*******************************************************/
double chi2_indep(int n_x, int n_y, int **h)
{
  int n;                      /* total number of sample points */
  double chi2;                                  /* chi^2 value */
  int k_x, k_y;                 /* number of contributing bins */
  int k, l;                                        /* counters */
  int *hx, *hy;                  /* one-dimensional histograms */

  hx = (int *) malloc(n_x*sizeof(int));            /* allocate */
  hy = (int *) malloc(n_y*sizeof(int));

  n = 0;            /* calculate total number of sample_points */
  for(k=0; k<n_x; k++)
    for(l=0; l<n_y; l++)
      n += h[k][l]; 
  
  k_x = 0;                  /* calculate 1-dim histogram for x */
  for(k=0; k<n_x; k++)
  {
    hx[k] = 0;
    for(l=0; l<n_y; l++)
      hx[k] += h[k][l];
    if(hx[k] > 0)                   /* does x bin contribute ? */
      k_x++;
  }

  k_y = 0;                  /* calculate 1-dim histogram for y */
  for(l=0; l<n_y; l++)
  {
    hy[l] = 0;
    for(k=0; k<n_x; k++)
      hy[l] += h[k][l];
    if(hy[l] > 0)                   /* does y bin contribute ? */
      k_y++;
  }

  chi2 = 0.0; 
  for(k=0; k<n_x; k++)                      /* calculate chi^2 */
    for(l=0; l<n_y; l++)
      if( (hx[k] != 0)&&(hy[l] != 0) )
	chi2 += pow(h[k][l]-(double) hx[k]*hy[l]/n, 2.0)/
	  ((double) hx[k]*hy[l]/n);

  free(hx);
  free(hy);
  return(gsl_cdf_chisq_Q(chi2, k_x*k_y - k_x -k_y + 1));
}


int main(int argc, char *argv[])
{
  int n;                                 /* number of sample points */
  int n_x, n_y;                  /* number of bins in x,y direction */
  double x0, y0;                             /* start of histograms */
  double dx, dy;                         /* width of histogram bins */
  int **h;                             /* two-dimensional histogram */
  int i, k, l;                                     /* loop counters */
  double u1, u2;                           /* U(0,1) random numbers */
  double r1, r2;                  /* standard normal random numbers */
  double x,y;                               /* final random numbers */
  double kappa;                          /* strength of correlation */
  int print_points, print_histo;                           /* flags */


  x0 = -5; dx = 0.2; n_x = 50;                        /* initialize */
  y0 = -5; dy = 0.2; n_y = 50;
  print_points = 0;
  print_histo = 0;

  h = (int **) malloc(n_x*sizeof(int *));
  for(k=0; k<n_x; k++)           /* allocate + initialize histogram */
  {
    h[k] = (int *) malloc(n_y*sizeof(int));
    for(l=0; l<n_y; l++)
      h[k][l] = 0;
  }

  kappa = 0.0;                   /* read arguments/ standard values */
  if(argc > 1)
    sscanf(argv[1], "%lf", &kappa);
  n = 10000;
  if(argc > 2)
    n = atoi(argv[2]);

  for(i=0; i<n; i++)                         /* perform experiments */
  {
    u1 = drand48();              /* generate Gaussian distr. number */
    u2 = drand48();
    r1 = sqrt(-2.0*log(1-u1))*sin(2*M_PI*u2);
    r2 = sqrt(-2.0*log(1-u1))*cos(2*M_PI*u2);
    x = r1;
    y = kappa*r1+r2;                  /* generate correlated number */
    if(print_points)
      printf("%f %f\n", x, y);
    k = (int) floor( (x-x0)/dx );      /* sort into 2-dim histogram */
    l = (int) floor( (y-y0)/dy );
    if( (k>=0)&&(k<n_x)&&(l>=0)&&(l<n_y))
      h[k][l]++;
  }

  printf("# p-value: %e\n", chi2_indep(n_x, n_y, h));

  if(print_histo)
    for(k=0; k<n_x; k++)                         /* print histogram */
      for(l=0; l<n_y; l++)
	printf("%d %d %d\n", k, l, h[k][l]);
  
  for(k=0; k<n_x; k++)                              /* free memeory */
    free(h[k]);
  free(h);

  return(0);
}
