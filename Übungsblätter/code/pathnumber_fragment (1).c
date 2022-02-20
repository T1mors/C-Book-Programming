/****************************************************************/
/*** Pathnumber: calculates number of paths in a plane        ***/
/*** one can go only in +x,+y or +xy direction                ***/
/*** (possibly with empty sites)                              ***/
/*** Introduction to Computational Physics                    ***/
/*** A.K. Hartmann                                            ***/
/*** Compile with cc -o pathnumber pathnumber.c -g -Wall      ***/
/*** run with: selectionsort <# of numbers>                   ***/
/*** University of Oldenburg, Germany 2011                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>

/** Calculates number of paths through plane of size lxl **/
/** The result is stored in num_paths[][]. The array     **/
/** occupied[][] stores for each site whether a pth can  **/
/** go there (1) or not (0).                             **/ 
void calc_paths(int l, double **num_paths, short int **occupied)
{
  int x, y;                 /* loop counters/ position in plane */

  num_paths[0][0] = 1;   


  /** INSERT HERE:                        **/
  /** initlialize values: paths at border **/

  /** INSERT HERE THE "DYNAMIC PROGRAMMING" CALCULATION OF **/
  /** OTHER ENTRIES OF pathnumber[][]                      **/     

}

/** main program: treats command line argument:              **/
/** size  of square plane                                    **/
int main(int argc, char *argv[])
{
  int l;                                       /* size of plane */
  double **num_paths;               /* number of paths to [x,y] */
  short int **occupied;                   /* is a site occupied */
  int x, y;                 /* loop counters/ position in plane */
  double p_occ = 1.00;                /* occupation probability */

  l = atoi(argv[1]);            /* read from calling parameters */

  /* setup dynamic memory */
  num_paths = (double **) malloc(l*sizeof(double *));
  occupied = (short int **) malloc(l*sizeof(short int *));
  for(x=0; x<l; x++)
  {
    num_paths[x] =  (double *) malloc(l*sizeof(double));
    occupied[x] = (short int *) malloc(l*sizeof(short int));
  }

  srand48(1000);          /* initialize random number generator */

  for(x=0; x<l; x++)          /* initlialize values: occupation */
    for(y=0; y<l; y++)
      if(drand48() < p_occ)
	occupied[x][y] = 1;
      else
	occupied[x][y] = 0;
  occupied[0][0] = 1;
	


  calc_paths(l, num_paths, occupied);            /* calculation */

  printf("# size num_paths\n");                /* shows results */
  printf("%d %f\n", l, num_paths[l-1][l-1]); 

  for(x=0; x<l; x++)                             /* free memory */
  {
    free(num_paths[x]);
    free(occupied[x]);
  }
  free(num_paths);
  free(occupied);
  return(0);
}
