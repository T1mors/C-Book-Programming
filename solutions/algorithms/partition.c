/*******************************************************************/
/*** Calculates for a set of integer a[0]..a[n-1] the partition  ***/
/*** into two subsets A1, A2 such that the difference            ***/
/*** |sum(A1)-sum(A2)| is minimized.                             ***/
/*** Dynamic programming is used.                                ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Dynamic programming                                ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n;   /* number of integers numbers */
  int *a;      /* array of interger numbers */
  int **part;     /* part[i,s] = 1 if within the integers a[0]..a[i] */
                  /*               there is a subset summing up to s */
                  /*             0, else                             */
  int i, s;                                         /* loop counters */
  int sum;

  n = argc-1;                              /* set number of integers */
  if(n==0)                                 /* no numbers to treat ? */
  {
    fprintf(stderr, "USAGE: %s {<integer>s}\n", argv[0]);
    exit(1);
  }

  a = (int *) malloc(n*sizeof(int));
  sum = 0;
  for(i=0; i<n; i++)                                /* read integers */
  {
    a[i] = atoi(argv[1+i]);
    sum += a[i];
  }
  part = (int **) malloc(n*sizeof(int *)); /* allocate dyn.prog.mat. */
  for(i=0; i<n; i++)
    part[i] = (int *) malloc((sum+1)*sizeof(int));

  for(s=0; s<=sum; s++)                       /* initialize matrix */
    part[0][s]=0;
  part[0][0] = 1;
  part[0][a[0]]=1;

  for(i=1; i<n; i++)                        /* calculate full matrix */
    for(s=0; s<=sum; s++)
      if( (part[i-1][s] ==1)||((s>=a[i])&&(part[i-1][s-a[i]]==1)))
	part[i][s] = 1;
      else
	part[i][s] = 0;

  s=sum/2;
  while(part[n-1][s] ==0)             /* look for minimum difference */
    s--;
  printf("smallest difference is %d\n", sum-2*s);

  for(i=0; i<n; i++)                                     /* clean up */
    free(part[i]);
  free(part);
  free(a);
  return(0);
}
