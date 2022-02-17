#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int t, *array, sum = 0;

    array = (int *) malloc (99*sizeof(int));
    for(t=0; t<100; t++)
        array[t] = t;
    for(t=0; t<100; t++)
        sum += array[t];
    printf("sum= %d\n", sum);
    free(array);
    return(0);
}
/*******************************************************************/
/*** Test program for demonstrating the features of valgrind     ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Debugging                                          ***/
/*** Section: memory checker                                     ***/
/*******************************************************************/

