/*******************************************************************/
/*** Implementation of histograms                                ***/
/*** Header file                                                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: A sample using C                                   ***/
/*******************************************************************/
#ifndef _HISTO_H_
#define _HISTO_H_

/** macros **/

#define _HISTO_NOM_      9         /* No. of (statistical) moments */

/** data types **/

/* holds statistical informations for a set of numbers:   */
/* histogram, # of Numbers, sum of numbers, squares, ...  */
typedef struct
{
  double           from, to;   /* range of histogram               */
  double              delta;   /* width of bins                    */  
  int                n_bins;   /* number of bins                   */
  double             *table;   /* bins                             */
  double          low, high;   /* No. of data out of range         */
  double   sum[_HISTO_NOM_];   /* sum of 1s, numbers, numbers^2 ...*/
} histo_t;

/** function prototypes **/
extern histo_t *histo_new(double from, double to, int n_bins);
extern void histo_delete(histo_t *his);
extern void histo_insert(histo_t *his, double number);
extern double histo_mean(histo_t *his);
extern void histo_fprint_pdf(FILE *file, histo_t *his);


#endif
