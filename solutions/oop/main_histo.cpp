/*******************************************************************/
/*** Implementation of histograms using C++                      ***/
/*** Main function                                               ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Object-oriented programming                        ***/
/*** Section: A primer in C++                                    ***/
/*******************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <iostream>

#include "histo++.h"

int main(int argc, char *argv[])
{
  int num_bins;                    // number of bins for histogram
  double mu;              // parameter of exponential distribution
  double number;                                  // random number
  int num_runs;              // amount of generated random numbers
  int run;                                         // loop counter
  int seed;                    // seed for random number generator

  mu = 1.0;                                  // set default values
  num_bins = 100;
  num_runs = 100000;
  seed = 1000;

  if(argc > 1)
    seed = atoi(argv[1]);             // read seed from arguments 
  srand48(seed);

#ifdef SOLUTION
  HistoM his(0.0, 10*mu, num_bins);
#else
  Histo his(0.0, 10*mu, num_bins);
#endif

  for(run=0; run<num_runs; run++)       // generate random numbers
  {
    number = -log(1-drand48())*mu;     // use simple srng drand48()
    his.insert(number);                        // put in histogram
  }

#ifdef SOLUTION
  std::cout << "Mean: " << his.mean() << std::endl;
#endif
  std::cout << "Distribution" << std::endl << his << std::endl;

#ifdef SOLUTION
  HistoM his2 = his;
  std::cout << "Mean2: " << his2.mean() << std::endl;
#endif
}

