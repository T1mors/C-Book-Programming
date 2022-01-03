/*******************************************************************/
/*** Function which returns a random number distributed          ***/
/*** according the exponential distribution                      ***/
/*** compile:                                                    ***/
/***        cc -o atoms atoms.c -lm -Wall                        ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Information retrieval, publishing, presentations   ***/
/*** Section: Three-dimensional figures with porvray             ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



/* stores data of one atom: */
typedef struct
{
  double        m;       /* mass of atom */
  double    sigma;       /* 'size' of atom for LJ */
  double  epsilon;       /* LJ energy parameter */
  double       *x;       /* position of atom */
  double       *v;       /* velocity of atom */
  double       *f;       /* force on atom */
} atom_t;

/* stores all global system data: */
typedef struct
{
  int               dim;       /* dimension of system */
  double             *l;       /* sizes of system */
  double            *lh;       /* half sizes of system */
  int                 N;       /* total number of particles */
  double            tau;       /* integration step size */
  double           tau2;       /* integration step size^2 */
  double              T;       /* temperature */
  double         virial;       /* Virial = sum_(i>j) r_ij*f_ij/3 */ 
} atoms_system_t;


/******************** atoms_setup() **********************/
/** Creates and initialises atom data                  **/
/** PARAMETERS: (*)= return-paramter                   **/
/**     system: global system parameters               **/
/** RETURNS:                                           **/
/**     array of atom data                             **/ 
/********************************************************/
atom_t *atoms_setup(atoms_system_t *system)
{
  atom_t *atom;          /* here all atom data is stored */
  int t, d;                              /* loop counters */

  atom = (atom_t *) malloc(system->N*sizeof(atom_t));
  for(t=0; t<system->N; t++)              /* initialize atoms */
  {
    atom[t].m = 1;
    atom[t].sigma = 1;
    atom[t].epsilon = 1;
    atom[t].x = (double *) malloc(system->dim*sizeof(double));
    atom[t].v = (double *) malloc(system->dim*sizeof(double));
    atom[t].f = (double *) malloc(system->dim*sizeof(double));
    for(d=0; d<system->dim; d++)         /* put atom randomly */
    {
      atom[t].x[d] = drand48()*system->l[d];
      atom[t].v[d] = 0;
    }
  }
  return(atom);
}




/***************** atoms_plot_cfg() **********************/
/** Prints configuration 'atom'  and system boundaries **/
/** to povray file with name cfg.pov.                  **/
/** Display with x-povray +I cfg.pov                   **/
/** PARAMETERS: (*)= return-paramter                   **/
/**     system: global system parameters               **/
/**       atom: atom data                              **/ 
/** RETURNS:                                           **/
/**      nothing                                       **/
/********************************************************/
void atoms_plot_cfg(atoms_system_t *system, atom_t *atom)
{
  char filename[1000];
  FILE *povfile;
  int t, d;                                   /* loop counters */
  double *r;                                       /* position */

  r = (double *) malloc(system->dim*sizeof(double));
  sprintf(filename, "cfg.pov");
  povfile = fopen(filename, "w");                 /* open file */
  fprintf(povfile, "#include \"colors.inc\"\n"   /* header etc */
	  "#include \"shapes.inc\"\n\n");
  fprintf(povfile, "background { color Yellow }\n\n");
  fprintf(povfile, "camera {\n  location <%f, %f, %f>\n", 
	  0.5*system->l[0], -1.5*system->l[1], 0.5*system->l[2]);
  fprintf(povfile, "  sky <0,0,1>\n");
  fprintf(povfile, "  look_at  <%f, %f, %f>\n}\n\n", 
	  0.5*system->l[0], 0.5*system->l[1], 0.5*system->l[2]);
  fprintf(povfile, 
	  "  light_source { <%f, %f, %f> color White}\n\n",
	  0.5*system->l[0], -0.5*system->l[1], 1.5*system->l[2]);
  fprintf(povfile, 
	  "  light_source { <%f, %f, %f> color White}\n\n",
	  -0.5*system->l[0], -0.5*system->l[1], 1.5*system->l[2]);

  fprintf(povfile,                   /* print system boundaries */
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  0.0, 0.0, 0.0, 
	  system->l[0], 0.0, 0.0);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  system->l[0], 0.0, 0.0, 
	  system->l[0], system->l[1], 0.0);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  system->l[0], system->l[1], 0.0, 
	  0.0, system->l[1], 0.0);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  0.0, system->l[1], 0.0, 
	  0.0, 0.0, 0.0);
  fprintf(povfile,                  
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  0.0, 0.0, system->l[2], 
	  system->l[0], 0.0, system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  system->l[0], 0.0, system->l[2], 
	  system->l[0], system->l[1], system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  system->l[0], system->l[1], system->l[2], 
	  0.0, system->l[1], system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  0.0, system->l[1], system->l[2], 
	  0.0, 0.0, system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  0.0, 0.0, 0.0, 
	  0.0, 0.0, system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  system->l[0], 0.0, 0.0, 
	  system->l[0], 0.0, system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  system->l[0], system->l[1], 0.0, 
	  system->l[0], system->l[1], system->l[2]);
  fprintf(povfile,       
	  "cylinder{ <%f, %f, %f>, <%f, %f, %f>, 0.25\n"
	  "   pigment { Red } }\n",
	  0.0, system->l[1], 0.0, 
	  0.0, system->l[1], system->l[2]);


  for(t=0; t<system->N; t++)                     /* print atoms */
  {
    for(d=0; d<system->dim; d++)
    {
      r[d] = atom[t].x[d];
      if(r[d] < 0)                   /* fold positions into box */
	  r[d] += floor(-r[d]/system->l[d]+1)*system->l[d];
	if(r[d] > system->l[d])
	  r[d] -= floor(r[d]/system->l[d])*system->l[d];	  
    }
    if(system->dim == 3)
      fprintf(povfile, 
	      "sphere { <%f,%f,%f>, %f\n    pigment { Blue }}\n",
	      r[0], r[1], r[2], 2*atom[t].sigma);
    else if(system->dim == 2)
      fprintf(povfile, 
	      "sphere { <%f,%f,%f>, %f\n    pigment { Blue }}\n",
	      r[0], r[1], 0.0, 2*atom[t].sigma);
  }
  fclose(povfile);
  free(r);
}


int main(int argc, char *argv[])
{
  atoms_system_t system;                 /* global system data */
  atom_t *atom;                             /* atom data */
  int t, d;                                  /* loop counters */
  double volume;
  int *n;

  system.dim = 3;                        
  system.tau = 0.001;
  system.N = 6*6*6;
 
  /** initialisation: **/
  system.l = (double *) malloc(system.dim*sizeof(double)); 
  system.lh = (double *) malloc(system.dim*sizeof(double));
  n = (int *)  malloc(system.dim*sizeof(int));
  system.tau2 = system.tau*system.tau;

  n[0] = (int) floor(pow(system.N, 1.0/system.dim)+0.005);
  system.N = n[0];
  for(d=1; d<system.dim; d++)
  {
    n[d] = n[0];
    system.N *= n[0];
  }
  for(d=0; d<system.dim; d++)
    system.l[d] = 6.0*n[0];


  volume = 1.0;
  for(d=0; d<system.dim; d++)
  {
    system.lh[d] = system.l[d]/2;
    volume *= system.l[d];
  }

  atom = atoms_setup(&system);
  atoms_plot_cfg(&system, atom);                      /* make 3d image */


  free(system.l);                                 /* clear up everything */
  free(system.lh);
  for(t=0; t<system.N; t++)
  {
    free(atom[t].x);
    free(atom[t].v);
    free(atom[t].f);
  }
  free(atom);
  free(n);
  return(0);
}
