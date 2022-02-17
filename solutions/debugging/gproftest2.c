/*******************************************************************/
/*** Test program for demonstrating the features of gprof        ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Debugging                                          ***/
/*** Section: Profiling                                          ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******************** calc_sum() ***********************************/
/** Calculates the sum of some numbers in interval                **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**              a: array                                         **/
/**            i,j: index range of numbers                        **/
/**                                                               **/
/** Returns:                                                      **/
/**         sum_(z=i..j) a[z]                                     **/
/*******************************************************************/
double calc_sum(double *a, int i, int j)
{
  int t; double sum= 0.0;
  for(t=i; t<=j ; t++)
    sum += a[t];
  return(sum);
}

