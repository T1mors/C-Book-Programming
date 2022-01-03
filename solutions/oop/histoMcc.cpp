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

#include <cmath>
#include <iostream>
#include <new>

#include "histo++.h"

/*********************** HistoM() *********************/
/** Copy Constructor: Creates a histogram (including **/
/** moments) as copy of passed histogram             **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       h: histogram                               **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
HistoM::HistoM(const HistoM &h) : Histo(h)
{
  num_moments = h.num_moments;
  sum = new double[num_moments];    // get memory for moments;

  for(int m=0; m<num_moments; m++)  // copy moments
    sum[m] = h.sum[m];
}



