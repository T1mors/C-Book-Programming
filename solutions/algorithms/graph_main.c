/****************************************************************/
/*** Main program for undirected graphs                       ***/
/*** A.K. Hartmann January 2008                               ***/
/*** Forgeschrittene Computersimulationen                     ***/
/*** University of Oldenburg, Germany 2008                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
#include "graphs.h"

int main(int argc, char **argv)
{
    int num_nodes;                     /* number of nodes in graph */
    gs_graph_t *g;

    num_nodes = 10;

    g = gs_create_graph(num_nodes);
    gs_insert_edge(g, 0, 5);
    gs_insert_edge(g, 0, 5);                 /* double for testing */
    gs_insert_edge(g, 5, 7);
    gs_insert_edge(g, 7, 0);
    gs_insert_edge(g, 3, 8);

    gs_write_graph(g, stdout);
    return(0);

}
