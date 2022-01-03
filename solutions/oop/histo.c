/*******************************************************************/
/*** Implementation of histograms                                ***/
/*** Basic functions                                             ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: A sample using C                                   ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "histo.h"

/******************* histo_new() **********************/
/** Creates a histogram and initializes it. Uses     **/
/** bins of uniform width.                           **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       from: start of histogram range             **/
/**         to: end of histogram range               **/
/**     n_bins: number of bins                       **/
/** RETURNS:                                         **/
/**     pointer to new element                       **/
/******************************************************/
histo_t *histo_new(double from, double to, int n_bins)
{
  histo_t *his;                              /* histogram pointer */
  int t;                                          /* loop counter */

  his = (histo_t *) malloc(sizeof(histo_t));
  if(his == NULL)                              /* enough memory ? */
  {
    fprintf(stderr, "out of memory in histo_new()");
    exit(1);
  }
  if(to < from)                    /* boundaries in wrong order ? */
  {
    double tmp;
    tmp = to; to = from; from = tmp;
    fprintf(stderr, "WARNING: exchanging from, to in histo_new()\n");
  }
  his->from = from;
  his->to = to;
  if( n_bins <= 0)           /* number of bins should be positive */
  {
    n_bins = 10;
    fprintf(stderr, "WARNING: setting n_bins=10 in histo_new()\n");
  }
  his->delta = (to-from)/(double) n_bins;                /* setup */
  his->n_bins = n_bins;
  his->low = 0;
  his->high = 0;
  for(t=0; t< _HISTO_NOM_ ; t++)     /* init. accumulated moments */
    his->sum[t] = 0.0;
  his->table = (double *) malloc(n_bins*sizeof(double));
  if(his->table == NULL)                       /* enough memory ? */
  {
    fprintf(stderr, "out of memory in histo_new()");
    exit(1);
  }
  else
    for(t=0; t<n_bins; t++)                     /* initalize bins */
      his->table[t] = 0;
  return(his);
}


/******************* histo_delete() *******************/
/** Deletes a histogram                              **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**      histo: histogram                            **/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
void histo_delete(histo_t *his)
{
  free(his->table);
  free(his);
}


/******************* histo_insert() *******************/
/** Inserts a number into histogram by incrementing  **/
/** the counter for the corresponding bin by one     **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**      histo: histogram                            **/
/**     number: to be inserted                       **/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
void histo_insert(histo_t *his, double number)
{
  int t;                           /* counter to access moments */
  double value;                           /* auxiliary variable */
  value = 1.0;
  for(t=0; t< _HISTO_NOM_; t++)
  {
    his->sum[t]+= value;                      /* raw statistics */ 
    value *= number;
  }
  if(number < his->from)               /* insert into histogram */
    his->low++;
  else if(number >= his->to)
    his->high++;
  else
    his->table[(int) floor( (number - his->from) / his->delta)]++;
}


/******************* histo_mean() *********************/
/** Returns mean of numbers in  histogram (0 if      **/
/** empty)                                           **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**      histo: histogram                            **/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
double histo_mean(histo_t *his)
{
  if(his->sum[0] == 0)
    return(0.0);
  else
    return(his->sum[1] / his->sum[0]);
}
