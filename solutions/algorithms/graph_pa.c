/*******************************************************************/
/*** Main program for undirected graphs                          ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A comprehensive practical guide to computer simulation      ***/
/*** World Scientific, Singapore 2014                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Graphs                                             ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "list.h"
#include "graphs.h"

int main(int argc, char **argv)
{
  int num_nodes;                             /* number of nodes in graph */
  int num_edges;                             /* number of edges in graph */
  gs_graph_t *g;
  int t, n;                                             /* loop counters */
  int num_real;                                /* number of realizations */
  int argz = 1;                   /* for treating command line arguments */
  int *histo;                                   /* histogram for degrees */
  int num_entries;                                       /* in histogram */
  int num_components;                                        /* in graph */
  int *comp;                                   /* component of each node */
  int size_largest, id_largest;                     /* largest component */
  int sum_sizes;                                 /* to calculate average */
  int d_max;                                           /* maximum degree */
  char name[1000], filename[1000], command[1000];   /* auxiliary strings */
  FILE *file;                                          /* to write graph */


  if(argc < 3)
  {
    printf("Usage %s <number nodes> <(initial) number edges>\n", argv[0]);
    exit(1);
  }

  num_real = 1000;
  num_nodes = atoi(argv[argz++]);                /* read number of nodes */
  num_edges =  atoi(argv[argz++]);    /* number of initially added edges */

  d_max = num_nodes;
  histo = (int *) malloc(d_max*sizeof(int));       /* init histogram etc */
  for(t=0;t < d_max; t++)
      histo[t] = 0;
  comp = (int *) malloc(num_nodes * sizeof(int));

  g = gs_create_graph(num_nodes);

  num_entries = 0;
  sum_sizes = 0;                   /* for average largest component size */
  for(t=0; t<num_real; t++)
  {
    gs_clear_graph(g);                          /* generate random graph */

    /* uncomment the following line for preferential attachment */
    /* gs_preferential_attachment(g, num_edges); */
    /* uncomment the following line for random graphs */
    gs_random_graph(g, num_edges); 

    for(n=0; n<g->num_nodes; n++)       /* insert degrees into histogram */
    {
      if(gs_degree(g, n)< d_max)
      {
	histo[gs_degree(g, n)]++;
	num_entries++;
      }
    }
    /* uncomment this for determining components */
    num_components = gs_components(g, comp);
    size_largest = gs_comp_largest(g, comp, num_components, &id_largest);
    sum_sizes += size_largest;

    /*gs_write_graph(g, stdout);*/
  }
  /* uncomment this for printing average size of largest component */
  printf("%d %f %f\n", num_nodes, (2.0*num_edges)/num_nodes,
	 (double) sum_sizes/(num_nodes*num_real));

  /* uncomment this for writing graph in .dot format */
  /*strcpy(name, "testgraph");
  sprintf(filename, "%s.dot", name);
  file = fopen(filename, "w");
  gs_dot_graph(g, file, 0);
  fclose(file);
  sprintf(command, "dot -Tps %s.dot > %s.ps", name, name);
  system(command);*/
  /*gs_dot_graph(g, stdout, 0);*/
  exit(1);

  for(t=0; t<d_max; t++)                              /* print histogram */
    if(histo[t] > 0)
      printf("%d %f\n", t, (double) histo[t]/num_entries);



  gs_delete_graph(g);
  free(histo);
  free(comp);

  return(0);

}
