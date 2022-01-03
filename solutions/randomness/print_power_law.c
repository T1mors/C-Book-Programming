/*******************************************************************/
/*** Prints pdf of power-law distribution                        ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Introduction to probability                        ***/
/*******************************************************************/

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  double gamma;                       /* parameter of distribution */
  double x;                                     /* argument of pdf */ 
  double prob;                            /* resulting probability */
  int argz = 1;             /* for treating command line arguments */

  sscanf(argv[argz++], "%lf", &gamma);             /* get argument */

  for(x=1; x<=20*gamma; x+=gamma/10)  
  {                          /* iterate to print full distribution */
    prob = gamma*pow(x,-gamma+1);
    printf("%f %f\n", x, prob);
  }
  return(0);
}
