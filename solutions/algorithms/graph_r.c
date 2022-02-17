/*******************************************************************/
/*** Implementation of graphs                                    ***/
/*** Function for generating a random graph                      ***/
/*** (solution to exercise)                                      ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Graphs                                             ***/
/*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
#include "graphs.h"


/******************* gs_random_graph() *******************/
/** Function adds exactly m randomly chosen edges to    **/
/** the graph.                                          **/
/** No self loops are allowed. No edge is allowed to    **/
/** appear twice!                                       **/
/** PARAMETERS: (*)= return-paramter                    **/
/**         (*) g: graph                                **/
/**             m: number of edges to be added per node **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_random_graph(gs_graph_t *g, int m)
{
  int t;
  int n1, n2;
  
  t = 0;
  while(t < m)                                /* insert m edges */
  {
    n1 = (int) floor(drand48()*g->num_nodes);
    do
      n2 = (int) floor(drand48()*g->num_nodes);
    while(n2==n1);             /* chose pair of different nodes */
    if(!gs_edge_exists(g, n1, n2))
    {
      gs_insert_edge(g, n1, n2);
      t++;
    }
  }
}



