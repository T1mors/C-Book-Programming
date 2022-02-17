/*******************************************************************/
/*** Sortes a set of data elements using mergesort               ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Divide and Conquer                                 ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "mergesort.h"

/*******************************************************************/
/** Sorts two set of data using the mergsort approach in          **/
/** ascending order.                                              **/
/**                                                               **/
/** Parameters: (*) = return parameter                            **/
/**            num: number of elements to be sorted               **/
/**           data: actual data elements                          **/ 
/**                                                               **/
/** Returns:                                                      **/
/**         array with elements sorted                            **/
/*******************************************************************/
animal_t *mergesort(int num, animal_t *data)
{
  animal_t *result, *result1, *result2;         /* sorted elements */
  int size1, size2;                /* sizes of two subsets of data */
  int t;         /* counter for putting elements into result array */
  int t1, t2;         /* for getting elemnts from result1/2 arrays */
    
  result = (animal_t *) malloc(num*sizeof(animal_t));

  if(num==1)                                 /* solve trivial case */
    result[0] = data[0];
  else                                                /* main work */
  {
    size1 = num/2; size2 = num - size1;
    result1 = mergesort(size1, data);             /* sort 1st half */
    result2 = mergesort(size2, data+size1);       /* sort 2nd half */

    t=0, t1=0; t2=0;          /* merge result1,result2 into result */
    while(t<num)      
      if( (t2==size2) || 
	   ((t1 < size1) && (result1[t1].weight<result2[t2].weight)))
	result[t++] = result1[t1++];
      else
	result[t++] = result2[t2++];

    free(result1); free(result2);
  }
  return(result);
}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int num_animals;         /* number of data elements to be sorted */
  animal_t *animal;                      /* array of data elements */
  animal_t *result;                        /* sorted data elements */
  int t;                                           /* loop counter */

  num_animals = 20;                       /* initialise everything */
  animal = (animal_t *) malloc(num_animals*sizeof(animal_t));
  for(t=0; t<num_animals; t++)
  {
    animal[t].animal_id = 2*t+1;
    animal[t].weight = (int) (1000*((double) rand()/RAND_MAX));
  }

  result = mergesort(num_animals, animal);           /* do sorting */

  for(t=0; t<num_animals; t++)                      /* show result */
    printf("result[%d] = (weight=%d, animal=%d)\n", 
	   t, result[t].weight, result[t].animal_id);

  free(animal); free(result);
  return(0);
}
