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


/******************** calc_sum_rec() *******************************/
/** Calculates the sum of some numbers in interval recursivly     **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**              a: array                                         **/
/**            i,j: index range of numbers                        **/
/**                                                               **/
/** Returns:                                                      **/
/**         sum_(z=i..j) a[z]                                     **/
/*******************************************************************/
double calc_sum_rec(double *a, int i, int j)
{
  if(i>=j)
    return(a[i]);
  else
    return(a[i]+calc_sum_rec(a,i+1,j));
}


/******************* calc_prod() ***********************************/
/** Calculates the product of some numbers in interval            **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**              a: array                                         **/
/**            i,j: index range of numbers                        **/
/**                                                               **/
/** Returns:                                                      **/
/**         prod_(z=i..j) a[z]                                    **/
/*******************************************************************/
double calc_prod(double *a, int i, int j)
{
  int t; double prod= 1.0;
  for(t=i; t<=j ; t++)
    prod *= a[t];
  return(prod);
}


/*************************** all1() ********************************/
/** Calculates the all possible sums/product over intervals of    **/
/** number in an array                                            **/
/** Parameters: (*) = return parameter                            **/
/**              n: size of array                                 **/
/**              a: array                                         **/
/**        (*) sum: will contain sum_(z=i..j) a[i]                **/  
/**       (*) prod: will contain prod_(z=i..j) a[i]               **/  
/**                                                               **/
/** Returns:                                                      **/
/**         (nothing)                                             **/
/*******************************************************************/
void all1(int n, double *a, double **sum, double **prod)
{
  int i, j; 

  for(i=0; i<n; i++)
    for(j=i; j<n; j++)
    {
      sum[i][j] = calc_sum(a, i, j);
      prod[i][j] = calc_prod(a, i, j);
    }
}


/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n;                                          /* size of array */
  double **sum, **prod, *a;       /* matrices and array of numbers */
  int t;

  n = atoi(argv[1]);                /* pass n as program parameter */
  a = (double *) malloc(n*sizeof(double));
  sum = (double **) malloc(n*sizeof(double *));
  prod = (double **) malloc(n*sizeof(double *));
  for(t=0; t<n; t++)
  {
    sum[t] = (double *) malloc(n*sizeof(double));
    prod[t] = (double *) malloc(n*sizeof(double));
  }

  for(t=0; t<n; t++)
    a[t] = t;
  
  for(t=0; t<n; t++)
    printf("%f\n", calc_sum(a,0,t));
  all1(n, a, sum, prod);

  for(t=0; t<n; t++)
  {
    free(sum[t]);
    free(prod[t]);
  }
  free(sum);
  free(prod);
  free(a);

  return(0);
}
