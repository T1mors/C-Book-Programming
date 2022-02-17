/*******************************************************************/
/*** Sample a discrete distribution function from a table.       ***/
/*** Linear-time algorithm by Walker using a precomputed table.  ***/
/*** Walker, A.J. (1997). An efficient method for generating     ***/
/*** discrete  random variables with general distributions,      ***/
/*** ACM Trans. Math. Softw. 3, pp. 253  as  implemented in      ***/
/*** K. Fukui & S. Todo, J. Comp. Phys.  228 (2009) 2629-2642    ***/
/*** Here: Poisson distribution (solution to exercise)           ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2014                            ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: exercises                                          ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_BINS 20

typedef struct
{
  int num_entries;        /* number of events */
  double *q;       /* splitting probabilities */
  int *a;               /* events for rand<=q */
  int *b;               /* events for rand>q  */
} discrete_variate_t;


/******************* setup_table() *********************/
/** Sets up table to generate discrete random numbers **/
/** in constant time using the Walker's method ,  as  **/
/** implemented in K. Fukui & S. Todo, J. Comp. Phys. **/
/** 228 (2009) 2629-2642                              **/
/** PARAMETERS: (*)= return-paramter                  **/
/**  num_entries: number of possible results          **/
/**            p: original probabilities              **/
/** RETURNS:                                          **/
/**      table with auxiliary variables               **/
/*******************************************************/
discrete_variate_t setup_table(int num_entries, double *p)
{
  int t, t0, t1, swap_a;
  discrete_variate_t table;
  double average_prob, swap_q;

  /* initialise table */
  table.num_entries = num_entries;
  table.q = (double *) malloc(num_entries*sizeof(double));
  table.a = (int *) malloc(num_entries*sizeof(int));
  table.b = (int *) malloc(num_entries*sizeof(int));
  for(t=0; t<num_entries; t++)
  {
    table.q[t] = p[t];
    table.a[t] = t;
    table.b[t] = -1;
  }

  average_prob = 1.0/num_entries;
  t0 = 0;
  t1 = num_entries-1;


  /** arrange elements such that all elements with **/
  /** q[t] > average_prob come first.              **/
  while(t0 < t1)
  {
    while((t0<t1)&&(table.q[t0] > average_prob))
           /* to 1st 'small' element from left */
      t0++;
    while((t0<t1)&&(table.q[t1] < average_prob))
            /* to 1st 'large' element from right */
      t1--;
    if(t0 < t1)    
    {
      swap_q = table.q[t0]; table.q[t0] = table.q[t1]; table.q[t1] = swap_q;
      swap_a = table.a[t0]; table.a[t0] = table.a[t1]; table.a[t1] = swap_a;
    }
  }
  /* now t1 points to the rightmost element larger than average_prob */
  

  /* rearrange table such that "each entry represents 'average_prob'" */
  for(t=num_entries -1; t>=1; t--)
  {
    if(table.q[t] < average_prob)
    {
      table.b[t] = table.a[t1];
      table.q[t1] -= (average_prob-table.q[t]);
      if(table.q[t1] < average_prob)
	t1--;
    }
  }
  for(t=0; t<num_entries; t++)   /* normalized cond. probabilities */
    table.q[t] /= average_prob;
  
  /*for(t=0; t<num_entries; t++)
    printf("%d %e %d %d\n", t, table.q[t], table.a[t], table.b[t]); */

  return(table);
}


/******************* draw_number() *********************/
/** Draw discrete number using the Walker's method.   **/
/** PARAMETERS: (*)= return-paramter                  **/
/**    table: for drawing discrete random numbers     **/
/** RETURNS:                                          **/
/**      random number                                **/
/*******************************************************/
int draw_number(discrete_variate_t * table)
{
  int entry;

  entry = (int) floor(table->num_entries*drand48());
  if(drand48() < table->q[entry])
    return(table->a[entry]);
  else
    return(table->b[entry]);
}


/***************** init_poisson_pmf() *****************/
/** Generates  array with distribution function      **/
/** for Poisson distribution with mean mu:           **/
/** F(k)=mu^k*exp(-mu)/x!                            **/
/** The size of the array is automatically adjusted. **/
/** PARAMETERS: (*)= return-paramter                 **/
/**   (*) n_p: p. to number of entries in table      **/
/**        mu: parameter of distribution             **/
/** RETURNS:                                         **/
/**     pointer to array with distribution function  **/
/******************************************************/
double *init_poisson_pmf(int *n_p, double mu)
{
  int k;                                     /* entry counter */
  int n;                         /* maximum number of entries */
  double prob;                                 /* probability */
  double *p;                       /* array for probabilities */
  n = 16;

  p = (double *)malloc(n*sizeof(double));   /* allocate array */
  prob = exp(-mu);                              /* initialize */
  k = 0;
  while(prob > 0)                               /* fill array */
  {
    p[k] = prob;
    if(k==n)                        /* end of array reached ? */
    {
	n *=2;                                 /* double size */
	p = realloc(p, n*sizeof(double));
    }
    k++;
    prob *= mu/k;
  }
  
  while(k<n)                         /* fill till end of array */
      p[k++] = 0.0;

  *n_p = n;
  return(p);
}


int main(int argc, char *argv[])
{
  int *histo;                                             /* histogram */
  int num_bins;                             /* number of outcomes/bins */
  int bin;
  double start_histo, end_histo;                 /* range of histogram */
  double delta;                                        /* width of bin */
  int t;                                               /* loop counter */
  int num_runs;                  /* number of generated random numbers */     
  double number;                                   /* generated number */
  double *p;                                 /* discrete probabilities */
  double sum;                                     /* for normalization */
  double mu;                      /* parameter of Poisson distribution */
  discrete_variate_t table;

  sscanf(argv[1], "%lf", &mu);
  num_runs = atoi(argv[2]);                         /* read parameters */

  p = init_poisson_pmf(&num_bins, mu);
  
  histo = (int *) malloc(num_bins*sizeof(int));
  for(t=0; t<num_bins; t++)                    /* initialise histogram */
      histo[t] = 0;        
  start_histo = -0.5; end_histo = num_bins-0.5;
  delta = (end_histo - start_histo)/num_bins; 
  
  table = setup_table(num_bins, p);

  for(t=0; t<num_runs; t++)                               /* main loop */
  {
    number = draw_number(&table);    
    bin = (int) floor( (number-start_histo)/delta);
    histo[bin]++;
  }

  if(num_runs == 0)
    for(t=0; t<num_bins; t++)
      printf("%d %e\n", t, p[t]);
  else
    for(t=0; t<num_bins; t++)            /* print normalized histogram */
      printf("%f %f\n", start_histo + (t+0.5)*delta,
	     histo[t]/(delta*num_runs));


  free(p);
  free(histo);
  free(table.q);
  free(table.a);
  free(table.b);

  return(0);
}
