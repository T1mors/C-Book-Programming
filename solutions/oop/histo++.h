/*******************************************************************/
/*** Implementation of histograms in C++                         ***/
/*** Header file                                                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: A primer in C++                                    ***/
/*******************************************************************/
#ifndef _HISTOPP_H_
#define _HISTOPP_H_

#include <iostream>

class Histo
{
 private:
  double           from, to;   // range of histogram    
  double              delta;   // width of bins  
  int             low, high;   // out of range numbers       
  int                n_bins;   // number of bins  
  double             *table;   // bins           

 public:
  Histo(double from, double to, int n_bins);  // constructor
  Histo();                                    // simple constructor
  Histo(const Histo& h);                      // copy constructor
  virtual ~Histo();                           // destructor
  void insert(double number);                 // insert data point
  Histo &operator=(const Histo &h);           // assignment operator

  friend std::ostream& operator << (std::ostream& os, const Histo& h);
};


class HistoM: public Histo
{
 private:
  int    num_moments;      // how many moments are stored
  double        *sum;      // sum of 1s, numbers, number^2, ...

 public:
  HistoM(double from, double to, int n_bins);  // Constructor
  HistoM(const HistoM& h);                     // copy constructor
  ~HistoM();                                   // Destructor

  void insert(double number);                 // insert data point
  double mean();                              // return mean
};


#endif
