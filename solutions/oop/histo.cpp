/*******************************************************************/
/*** Implementation of histograms in C++                         ***/
/*** Main member functions                                       ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: A primer in C++                                    ***/
/*******************************************************************/

#include <cmath>
#include <iostream>
#include <new>

#include "histo++.h"

/*********************** Histo() **********************/
/** Constructor: Creates a histogram and             **/
/** bins of uniform width.                           **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       from: start of histogram range             **/
/**         to: end of histogram range               **/
/**     n_bins: number of bins                       **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
Histo::Histo(double h_from, double h_to, int h_n_bins)
{
  from = h_from;                 // store parameters
  to = h_to;
  if(to < from)                  // boundaries in wrong order ? 
  {
    double tmp;
    tmp = to; to = from; from = tmp;
    fprintf(stderr, "WARNING: exchanging from, to in Histo()\n");
  }
  low = 0;
  high = 0;
  n_bins = h_n_bins;
  delta = (to-from)/n_bins;      // calculate bin width
  table = new double[n_bins];    // get memory for bins;

  for(int t=0; t<n_bins; t++)    // Initialize bins
    table[t] = 0;
}


/***************** operator <<() **********************/
/** Prints histogram            **/
/** PARAMETERS: (*)= return-paramter                 **/
/**       os: Output stream                          **/
/**         h: histogram                             **/
/** RETURNS:                                         **/
/**     output stream                                **/
/******************************************************/
std::ostream& operator << (std::ostream& os, const Histo& h)
{

  int i;
  os << "# below:" << h.from << std::endl;
  os << "# above: " << h.to << std::endl;
  os << "# from: " << h.from << " delta: " << h.delta;
  os << " nbins: " << h.n_bins << std::endl;
  for(i=0; i<h.n_bins; i++)
    os << i << " " << h.table[i] << std::endl;
  
  return(os); 

}


/*********************** Histo() **********************/
/** Copy Constructor: Creates a histogram and        **/
/** bins of uniform width given by passed histogram  **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       h: histogram                               **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
Histo::Histo(const Histo &h)
{
  from = h.from;                 // store parameters
  to = h.to;
  low = h.low;
  high = h.high;
  n_bins = h.n_bins;
  delta = h.delta;               // bin width
  table = new double[n_bins];    // get memory for bins;

  for(int t=0; t<n_bins; t++)    // copy bin entries
    table[t] = 0;
}

/*********************** Histo() **********************/
/** Constructor: Creates a histogram over [0,1] with **/
/** 10 bins                                          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
Histo::Histo()
{
  Histo(0, 1, 10);   // Use standard values
}


/****************** = operator() **********************/
/** Assigns content of histogram to given histogram  **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       h: histogram                               **/
/** RETURNS:                                         **/
/**     Refernce to assigned object                  **/
/******************************************************/
Histo& Histo::operator=(const Histo &h)
{
  if( this != &h )                 // no self assignment
  {
    from = h.from;                 // store parameters
    to = h.to;
    n_bins = h.n_bins;
    delta = h.delta;               // bin width
    delete[] table;                  // delete old table
    table = new double[n_bins];    // get memory for bins;
    low = h.low;
    high = h.high;

    for(int t=0; t<n_bins; t++)    // copy bin entries
      table[t] = h.table[t];
  }
  return( *this);
}


/****************** destructor() **********************/
/** Destroy histogram                                **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
Histo::~Histo()
{
  delete[] table;
}



/********************** insert() **********************/
/** Insert data point into histogram                 **/
/** PARAMETERS: (*)= return-paramter                 **/
/**    number: data point                            **/
/**                                                  **/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
void Histo::insert(double number)
{
  if(number < from)               // insert into histogram 
    low++;
  else if(number >= to)
    high++;
  else
    table[(int) floor( (number - from) / delta)]++;
}


/*********************** HistoM() **********************/
/** Constructor: Creates a histogram and             **/
/** bins of uniform width, includign moments         **/ 
/** PARAMETERS: (*)= return-paramter                 **/
/**       from: start of histogram range             **/
/**         to: end of histogram range               **/
/**     n_bins: number of bins                       **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
HistoM::HistoM(double h_from, double h_to, int h_n_bins) :
  Histo(h_from, h_to, h_n_bins)
{
  num_moments = 8;          // allocate moments
  sum = new double[num_moments]; 

  for(int m=0; m<num_moments; m++)
    sum[m] = 0;
}


/****************** destructor() **********************/
/** Destroy histogram with moments                   **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     ---                                          **/
/******************************************************/
HistoM::~HistoM()
{
  delete[] sum;
}



/********************** insert() **********************/
/** Insert data point into histogram                 **/
/** PARAMETERS: (*)= return-paramter                 **/
/**    number: data point                            **/
/**                                                  **/
/** RETURNS:                                         **/
/**     (nothing)                                    **/
/******************************************************/
void HistoM::insert(double number) 
{
  double value = 1.0;         // auxiliary variable

  for(int m=0; m<num_moments; m++)
  {
    sum[m]+= value;;          // raw statistics 
    value *= number;
  }
  Histo::insert(number);      // perform insert for parent class
}





