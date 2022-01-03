/*******************************************************************/
/*** Calculates all permutations of a given array of numbers     ***/
/*** using a recursive approach                                  ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Iteration and recursion                            ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******************* permutation() *************************/
/** Obtains all permutations of positions 0..n-1 of a     **/
/** given array 'a' of numbers and prints them,           **/
/** including the higher index entries (from 0..n_max-1). **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**            n: current range                           **/
/**        n_max: size of array                           **/
/**            a: array                                   **/
/** Returns:                                              **/
/**        (nothing)                                      **/
/***********************************************************/
void permutation(int n, int n_max, int *a)
{
  int t;
  int exch;

  if(n==1)                                       /* print solution */
  {
    for(t=0; t<n_max; t++)
      printf("%d ", a[t]);
    printf("\n");
  }
  else
    for(t=0; t<n; t++)
    {
      exch = a[n-1]; a[n-1] = a[t]; a[t] = exch;
      permutation(n-1, n_max, a);
      exch = a[n-1]; a[n-1] = a[t]; a[t] = exch;
    }      
}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n;            /* number of which factorial is to be computed */    
  int *a;                                     /* array for numbers */
  int t;                                           /* loop counter */
  n = atoi(argv[1]);             /* n= first command line argument */
  a = malloc(n*sizeof(int));
  for(t=0; t<n; t++)
    a[t]=t+1;
  permutation(n, n, a);

  free(a);
  return(0);
}
