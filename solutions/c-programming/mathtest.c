/*******************************************************************/
/*** Calls some mathematical functions                           ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Basic C programs                                   ***/
/*******************************************************************/

#include <stdio.h>
#include <math.h>

int main()
{
  double z= 0.25*M_PI;
  printf("%f %f %f\n", sin(z), cos(z), tan(z));
  printf("%f %f \n", asin(sqrt(2.0)/2.0)/M_PI, acos(0.0)/M_PI);
  printf("%f %f %f %f\n", pow(M_E, 1.5), exp(1.5), log(1.0), log(M_E));
  printf("%f %f %f\n", fabs(-3.4), floor(-3.4), floor(3.4)); 
  printf("%f %f\n", fmax(1.3, 2.67), fmin(1.3, 2.67));
  printf("%e %e %e %e\n", erf(0.0), erf(1.0), erf(2.0), erf(5.0));
  printf("%f %f %f %f\n", tgamma(4.0), tgamma(4.5), 
	                  tgamma(5.0), exp(gamma(5.0)) );
  printf("%f %f %f\n", j0(2.0), j1(2.0), jn(1.0,2.0));
  return(0);
}
