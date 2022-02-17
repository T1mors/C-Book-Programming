/*******************************************************************/
/*** Implementation of graphs                                    ***/
/*** Calculation of the connected components                     ***/
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

/******************* gs_components() *********************/
/** Determines connected components of (undirected)     **/
/** graph.                                              **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**      (*) comp: ID of component for each node        **/
/** RETURNS:                                            **/
/**    number of components                             **/
/*********************************************************/
int gs_components(gs_graph_t *g, int *comp)
{
  int n1, n2, nn;                            /* nodes/loop counters */
  int *candidate;                           /* nodes still to treat */
  int num_candidates; 
  int num_components = 0;      /* number of components so far found */
  elem_t *neighb;                   /* for iterating over neighbors */


  candidate = (int *) malloc(g->num_nodes * sizeof(int));
  for(n1=0; n1<g->num_nodes; n1++)
    comp[n1] = -1;                   /* initializes as non-assigned */

  for(n1=0; n1<g->num_nodes; n1++)    /* all poss. components seeds */
  {
    if(comp[n1] == -1)             /* not yet part of a component ? */
    {
      comp[n1] = num_components;
      candidate[0] = n1;
      num_candidates = 1;
      while(num_candidates > 0)   /* still nodes current component? */
      {
	n2 = candidate[--num_candidates];         /* next candidate */
	neighb = g->node[n2].neighbors;
	while(neighb != NULL)           /* go through all neighbors */
	{
	  nn = neighb->info;
	  if(comp[nn] == -1)         /* not yet part of component ? */
	  {
	    comp[nn] = num_components;         /* add to candidates */
	    candidate[num_candidates++] = nn;
	  }
	  neighb = neighb->next;
	}
      }
      num_components++;
    }
  }

  free(candidate);
  return(num_components);
}


/***************** gs_comp_largest() *********************/
/** Determines connected components of (undirected)     **/
/** graph.                                              **/
/** PARAMETERS: (*)= return-paramter                    **/
/**                g: graph                             **/
/**             comp: ID of component for each node     **/
/**         num_comp: number of components              **/
/** (*) id_largest_p: p. to id of largest comp.         **/
/** RETURNS:                                            **/
/**    size of largest component                        **/
/*********************************************************/
int gs_comp_largest(gs_graph_t *g, int *comp, int num_comp, int *id_largest_p)
{
  int c;                            /* component counter */
  int n1;                                /* node counter */
  int *size;                   /* size of each component */
  int size_largest, id_largest;         /* largest comp. */

  size = (int *) malloc(num_comp*sizeof(int));
  for(c=0; c<num_comp; c++)
    size[c] = 0;

  for(n1=0; n1<g->num_nodes; n1++)    /* determine sizes */
    size[comp[n1]]++;

  id_largest = 0;                   /* determine largest */
  for(c=1; c<num_comp; c++)
    if(size[c] > size[id_largest])
      id_largest = c;

  *id_largest_p = id_largest;          /* return results */
  size_largest = size[id_largest];
  free(size);
  return(size_largest);
}
