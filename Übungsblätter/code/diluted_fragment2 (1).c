/**********************************************************/
/*** Simulation of diluted ferromagnet                  ***/
/***                                                    ***/
/*** Version 0.1.0.0                                    ***/
/***                                                    ***/
/*** A.K. Hartmann May 2005                             ***/
/***                                                    ***/
/**********************************************************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "percol.h"

/* function commentary header (empty): */

/*******************  *****************/
/**  **/
/** PARAMETERS: (*)= return-paramter         **/
/**  **/
/** RETURNS:                               **/
/**  **/
/******************************************/


/****************** r_0_1() **************************/
/** Random number distributed  uniformly in [0,1)   **/
/** PARAMETERS: (*)= return-parameter               **/
/**                                                 **/
/** RETURNS:                                        **/
/**    random number                                **/
/*****************************************************/
double r_0_1()
{
  double value;
  do
    value = ((double)rand())/(RAND_MAX);
  while(value == 1.0);
  return(value);
}

/****************** diluted_energy() *************************/
/** Caluclates energy of configuration                      **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**      num_n: number of neighbours                        **/
/**          N: number of spins                             **/
/**       next: gives neighbours next[0..N][0..num_n+1](t2)**/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     energy                                              **/
/*************************************************************/
double diluted_energy(short int *spin, int num_n, int N, int *next, 
		 short int *e)
{
  int t,r;
  double energy;

  energy = 0.0;
  for(t=1; t<=N; t++)                            /* loop over all spins */
    if(e[t] != 0)
      for(r=0; r<num_n; r++)                        /* calulate energy */
	energy += -spin[t]*spin[NEXT(t, r)]*e[NEXT(t,r)];
  return(energy/2.0);
}

/************************** diluted_print() ******************/
/** prints configuration line by line                       **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**          N: number of spins                             **/
/**       line: number of spins in one line                 **/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     nothing                                             **/
/*************************************************************/
void diluted_print(short int *spin, int N, int line, short int *e)
{
  int t;

  for(t=1; t<=N; t++)                       /* loop over all spins */
  {

    /** please complete here **/
  }
}

/****************** diluted_magnetisation() ******************/
/** Caluclates magnetisation of configuration               **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**          N: number of spins                             **/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     magnetization                                       **/
/*************************************************************/
double diluted_magnetisation(short int *spin, int N, short int *e)
{

  int t;
  double mag;

    /** please complete here **/


  return(mag);

}

/****************** diluted_mag_cluster() ********************/
/** Caluclates magnetisation of configuration just for spins**/
/** of given cluster 'cluster_id'                           **/
/** PARAMETERS: (*)= return-paramter                        **/
/**       spin: spin-configuration [1..N]                   **/
/**          N: number of spins                             **/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/** RETURNS:                                                **/
/**     magnetization                                       **/
/*************************************************************/
double diluted_mag_cluster(short int *spin, int N, short int *e, 
			   int *cluster, int cluster_id)
{
  int t;
  double mag;

  mag = 0.0;
  for(t=1; t<=N; t++)                       /* loop over all spins */
    if(cluster[t] == cluster_id)
      mag += spin[t]*e[t];                /* calculate magnetisation */
  return(mag);
}

/****************** diluted_mc_T() ***************************/
/** Does metropolis MC-simulation with diluted ferromagnet  **/
/** at T>0.                                                 **/
/** PARAMETERS: (*)= return-paramter                        **/
/**  (*)  spin: spin-configuration [1..N]                   **/
/**      num_n: number of neighbours in lattice             **/
/**          N: number of spins                             **/
/**       next: gives neighbours next[0..N][0..2*dim+1] (t2)**/
/**          e: sites arre ocupied (e[i]=1) or empty (=0)   **/
/**  mc_sweeps: number of MC sweeps                         **/
/**          T: temparture in units of j                    **/
/** RETURNS:                                                **/
/**     nothing                                             **/
/*************************************************************/
void diluted_mc_T(short int *spin, int num_n, int N, int *next, 
		 short int *e, int mc_sweeps, double T)
{
    int num_mc;
    double delta_e;

    for(num_mc=0; num_mc<mc_sweeps*N; num_mc++)                   /* do MC */
    {

      /** complete here **/
    }
}



