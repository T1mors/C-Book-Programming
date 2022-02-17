/*******************************************************************/
/*** Simple linear congruential pseudo random number generator   ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Generating (pseudo) random numbers                 ***/
/*******************************************************************/

#include <stdio.h>
#include <math.h>

#define RNG_MODULUS  32768            /* modulus */


/*********************** lin_con() ********************/
/** Linear congruential pseudo random number         **/
/** generator according I_{n+1} = (aI_n+c) mod m     **/
/** Driver function for all functionalities          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**   set_seed: seed is set if 1                     **/
/**       seed: seed value if to set                 **/
/** RETURNS:                                         **/
/**     pseudo random number / seed                  **/
/******************************************************/
int lin_con(int set_seed, int seed)
{
  static int x = 1000;        /* current random number */
  const int a = 12351;                   /* multiplier */
  const int c = 1;                            /* shift */

  if(set_seed)                           /* new seed ? */
    x = seed;
  else                          /* new random number ? */
    x = (a*x+c) % RNG_MODULUS;

  return(x);
}

/******************** rn_lin_con() ********************/
/** Returns a pseudo random integer number from      **/
/** linear congruential generator ccording           **/
/** Number is in interval [0,RNG_MODULUS-1]          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     pseudo random number                         **/
/******************************************************/
int randn_lin_con()
{
  return(lin_con(0,0));
}

/******************* drn_lin_con() ********************/
/** Returns a pseudo random double in [0,1) numbe    **/
/** from linear congruential generator ccording      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     pseudo random number                         **/
/******************************************************/
double drand_lin_con()
{
  return( (double) lin_con(0,0) / RNG_MODULUS);
}



/****************** seed_lin_con() ********************/
/** Sets seed for linear congruential generator      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**                                                  **/
/** RETURNS:                                         **/
/**     pseudo random number                         **/
/******************************************************/
void srand_lin_con(int seed)
{
  lin_con(1, seed);
}


int main(int argc, char *argv[])
{
  int num_numbers = 10000;   /* number of random numbers */
  double r1, r2;   /* random numbers */     
  int i;                                 /* loop counter */

  r1 = drand_lin_con();
  for(i=0; i<num_numbers; i++)
  {
    r2 = r1;                         /* store old number */
    r1 = drand_lin_con();                    /* new number */
    printf("%f %f\n", r2, r1); /* plot correlation tupel */
  }

  return(0);
}
