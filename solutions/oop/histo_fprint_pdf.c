/*******************************************************************/
/*** Implementation of histograms                                ***/
/*** Prints histogram as pdf (solution to exercise)              ***/
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

/************* histo_fprint_pdf() *********************/
/** Prints moments of histogram and bin counts for   **/
/** outliers to file.                                **/
/** Prints also histogram as pdf                     **/ 
/** Prints also Gaussian standard error bars or      **/
/** bin counts (normalized)                          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       file: file pointer                         **/          
/**      histo: histogram                            **/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
void histo_fprint_pdf(FILE *file, histo_t *his)
{
  int t;                                /* loop counter for bins */
  double value;                      /* stores temporrary value  */

  if(( his->sum[0]) == 0)                         /* error check */
    fprintf(file, "# statistic is empty !\n");
  else
  {
    int tm;
    fprintf(file, "# moments:");                 /* print moments */
    for(tm=0; tm<_HISTO_NOM_; tm++)
      fprintf(file, " %d: %f", tm, his->sum[tm]/ his->sum[0]);
    fprintf(file, "\n");
    fprintf(file, "# %e elems too small, %e elems too big\n",
            his->low, his->high);
    for(t=0; t < his->n_bins; t++)                  /* print pdf */
    {
      value = ((double)his->table[t])/(his->sum[0]);
      fprintf(file, "%e %e %e\n", 
	      his->from + (((double) t)+0.5) * his->delta,
		value/his->delta, 
	      sqrt(value*(1-value)/his->sum[0])/his->delta);
      }
  }
}


