/*******************************************************************/
/*** Implementation of histograms in C++                         ***/
/*** Solutions for exercise                                      ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: exercises                                          ***/
/*******************************************************************/

#include <math.h>
#include <iostream>
#include <new>

#include "histo++.h"

/*********************** HistoM() *********************/
/** Copy Constructor: Creates a histogram (including **/
/** moments) as copy of argument histogram           **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       h: histogram                               **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
HistoM::HistoM(const HistoM &h) : Histo(h)
{
  num_moments = h.num_moments;
  sum = new double[num_moments];    // get memory for moments;

  int m;                         // copy moments
  for(m=0; m<num_moments; m++)
    sum[m] = h.sum[m];
}


/************************ mean() **********************/
/** Calculates mean from  histogram                  **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     mean                                         **/
/******************************************************/
double HistoM::mean() 
{
  return(sum[1]/sum[0]);
}





