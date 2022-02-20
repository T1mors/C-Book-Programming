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
#include "diluted.h"

int main(int argc, char** argv)
{
  int dim;                                          /* dimension of system */
  int num_n;                             /* number of neighbors in lattice */
  int num_sweeps, sweep;                              /* ... of simulation */
  double T;                                                 /* temperature */ 
  double p_hole;                                 /* prob. pf having a hole */
  int real_id, real_id0;                     /* ID of realization (= seed) */
  int num_real;                                  /* number of realisations */
  int seed;                       /* seed of generator for simulation part */
  int size;                 /* size of system (if all sides have same size */
  int *l;                                               /* sizes of system */
  short int *spin;                                   /* spin configuration */
  short int *e;                       /* whether a spin is occupied or not */
  double energy, mag, mag2;                             /* ... of spin cfg */

  int do_up;                             /* start with all spins aligned ? */

  int N, N_spins;                                /* number of sites, spins */
  int *next;                                        /* neighbour relations */
  int *cluster;                                 /* cluster id of each spin */
  int num_cluster;                              /* number of spin clusters */
  int size_largest, id_largest;            /* for largest cluster of spins */
  int t;                                                   /* loop counter */
  int d;                                   /* loop counter over dimensions */
  int argz = 1;                  /* counter for treating arguments/options */
  int do_stdout;                               /* write output to stdout ? */
  FILE *file;
  char filename[1000], appendix[1000];
  int delta_t;                     /* write out result every delta_t steps */


  T = 2.2691853; p_hole = 0.0; real_id0 = 1000; num_real = 1; dim = 2; 
  do_up = 0;                                             /* default values */
  seed = 10000; strcpy(appendix, ""); do_stdout = 0; delta_t = 1;

  while((argz<argc)&&(argv[argz][0] == '-'))              /* treat options */
  {
    if(strcmp(argv[argz], "-T") == 0)
    {
      sscanf(argv[++argz], "%lf", &T);
    }
    else if(strcmp(argv[argz], "-p") == 0)
    {
      sscanf(argv[++argz], "%lf", &p_hole);
    }
    else if(strcmp(argv[argz], "-up") == 0)
    {
      do_up = 1;
    }
    else if(strcmp(argv[argz], "-seed") == 0)
    {
      sscanf(argv[++argz], "%d", &seed);
    }
    else if(strcmp(argv[argz], "-real") == 0)
    {
      sscanf(argv[++argz], "%d", &real_id0);
    }
    else if(strcmp(argv[argz], "-num") == 0)
    {
      sscanf(argv[++argz], "%d", &num_real);
    }
    else if(strcmp(argv[argz], "-delta") == 0)
    {
      sscanf(argv[++argz], "%d", &delta_t);
    }
    else if(strcmp(argv[argz], "-stdout") == 0)
    {
      do_stdout = 1;
    }
    else if(strcmp(argv[argz], "-appendix") == 0)
    {
      strcpy(appendix, argv[++argz]);
    }
    else
    {
      fprintf(stderr, "unkown option: %s\n", argv[argz]);
      exit(1);
    }
    argz++;
  }

  if( (argc-argz) < 1)
  {
    fprintf(stderr, "USAGE: %s {<options>} <L> <#sweeps>\n", argv[0]);
    fprintf(stderr, "   OPTIONS:\n");
    fprintf(stderr, "       -T <T>: set temperature (d:%2.1f)\n", T);
    fprintf(stderr, "       -p <p>: set hole prob. (d:%2.1f)\n", p_hole);
    fprintf(stderr, "          -up: start with all spins up (d:random)\n");
    fprintf(stderr, "    -real <r>: seed for realisation (d:%d)\n", seed);
    fprintf(stderr, "    -num <n>: number of realisation (d:%d)\n", num_real);
    fprintf(stderr, "    -seed <s>: seed for rnd number (d:%d)\n", seed);
    fprintf(stderr, "    -delta <t>: writeout interval (d:%d)\n", delta_t);
    fprintf(stderr, "-appendix <a>: for output filename\n");
    fprintf(stderr, "      -stdout: write output to stdout\n");
    exit(1);
  }
  size = atoi(argv[argz++]);
  num_sweeps = atoi(argv[argz++]);

  l = (int *) malloc(dim*sizeof(int));     /* allocations/ intializations */
  l[0] = size;
  for(d=1; d<dim; d++)
    l[d] = l[0];
  /*mf_init_arr(dim, l, 1, &(n), &N, &(next), &(tfeld), 0);*/
  next = percol_init_next(dim, l, &N);
  num_n = 2*dim;
  spin = (short int *) malloc((N+1)*sizeof(short int));
  e = (short int *) malloc((N+1)*sizeof(short int));
  cluster = (int *) malloc((N+1)*sizeof(int));

  for(real_id = real_id0; real_id < real_id0+num_real; real_id++)
  {                                          /* loop over all realizations*/
    sprintf(filename, "dilutedL%dp%3.2fID%dT%4.3f%s.out", size, p_hole, 
	    real_id, T, appendix);
    if(do_stdout)
      file = stdout;
    else
      file = fopen(filename, "w");
    fprintf(file,"# run: ");
    for(t=0; t<argz; t++)
      fprintf(file, "%s ", argv[t]);
    fprintf(file, "\n");

    srand(real_id);
    srand48(real_id);
    {
      double r_num;

      N_spins = 0;
      for(t=1; t<=N; t++)                   /* initialize disorder randomly */
      {
	r_num = r_0_1();
	if(r_num<p_hole)
	  e[t] = 0;
	else
	{
	  e[t] = 1;
	  N_spins++;
	}
      }
    }

    num_cluster = percol_cluster(num_n, N, next, e, cluster);
    size_largest = percol_largest(N, num_cluster, cluster, &id_largest);
    
    fprintf(file, "# Info realisation %d:" 
	   "numb. clusters=%d, id_largest=%d, size_largest = %d\n", 
	   real_id, num_cluster, id_largest, size_largest);

    fprintf(file, "# time energy magnetisation\n");
    srand(seed);
    for(t=1; t<=N; t++)                          /* initialize spins randomly */
      if(do_up || (r_0_1()<0.5))
	spin[t] = 1;
      else
	spin[t] = -1;
    
    for(sweep=0; sweep<num_sweeps/delta_t; sweep++)
    {
      diluted_mc_T(spin, num_n, N, next, e, delta_t, T);
      energy = diluted_energy(spin, num_n, N, next, e)/N_spins;
      mag = diluted_magnetisation(spin, N, e)/N_spins;
      mag2 = diluted_mag_cluster(spin, N, e, cluster, id_largest)/size_largest;
      fprintf(file, "%d %f %f %f\n", (sweep+1)*delta_t, energy, mag, mag2);
    }
    /*diluted_print(spin, N, l[0], e);*/
    fclose(file);
  }

  free(l);
  free(next);
  free(spin);
  free(e);
  free(cluster);

  return(0);
}
