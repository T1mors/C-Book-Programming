/*******************************************************************/
/*** Calculates cumulative probability Q for results of          ***/
/*** gnuplot fit                                                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: General estimators                                 ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_cdf.h>


int main(int argc, char *argv[])
{
  double WSSRndf;
  int ndf;

  if(argc != 3)
  {
    printf("USAGE %s <ndf> <WSSR/ndf>\n", argv[0]);
    exit(1);
  }
  ndf = atoi(argv[1]);
  sscanf(argv[2], "%lf", &WSSRndf);
  printf("# Q=%e\n", gsl_cdf_chisq_Q(ndf*WSSRndf, ndf));

  return(0);
}
