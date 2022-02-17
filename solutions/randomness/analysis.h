/*******************************************************************/
/*** Implementation of data analysis function                    ***/
/*** Header file                                                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomnness and Statistics                         ***/
/*** Section: basic data analysis, resampling using bootstrap    ***/
/*******************************************************************/
#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

/** macros **/

/** data types **/


/** function prototypes **/
extern double mean(int n, double *x);
extern double variance(int n, double *x);
extern double bootstrap_variance(int n, double *x, int n_resample,
				 double (*f)(int, double *));
extern void bootstrap_ci(int n, double *x, int n_resample,
			 double alpha, double (*f)(int, double *),
			 double *low, double *high);


#endif
