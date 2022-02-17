/*******************************************************************/
/*** Implementation of graphs                                    ***/
/*** Functions                                                   ***/
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
#include "graphs_lists.h"

/******************* gs_create_graph() ********************/
/** Creates a graph with a fixed number of nodes and    **/
/** no edges.                                           **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      num_nodes: number of nodes                     **/
/** RETURNS:                                            **/
/**     pointer to created graph                        **/
/*********************************************************/
gs_graph_t *gs_create_graph(int num_nodes)
{
    gs_graph_t *g;
    int n;

    g = (gs_graph_t *) malloc(sizeof(gs_graph_t));  /* allocate */
    g->node = (gs_node_t *) malloc(num_nodes*sizeof(gs_node_t));

    g->num_nodes = num_nodes;                     /* initialise */
    for(n=0; n<num_nodes; n++)
	g->node[n].neighbors = NULL;

    return(g);
}



/******************* gs_insert_edge() ********************/
/** Insert undirected edge (from,to) into graph         **/
/** if the edge does not exists so far.                 **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**      from, to: id of nodes                          **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_insert_edge(gs_graph_t *g, int from, int to)
{
    elem_t *elem1, *elem2, *list;

    list = g->node[from].neighbors;            /* edge exists? */
    while( list != NULL )
    {
      if(list->info == to)                              /* yes */
	return;
      list = list->next;
    }

    elem1 = create_element(to);  /* create neighbor for 'from' */
    g->node[from].neighbors = 
	insert_element(g->node[from].neighbors, elem1, NULL);
    elem2 = create_element(from);  /* create neighbor for 'to' */
    g->node[to].neighbors =             
	insert_element(g->node[to].neighbors, elem2, NULL);
}


/******************* gs_edge_exists() ********************/
/** Tests whether undirected edge (from,to) in graph    **/
/** exists already.                                     **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**      from, to: id of nodes                          **/
/** RETURNS:                                            **/
/**     1 if edge exists, 0 else                        **/
/*********************************************************/
int gs_edge_exists(gs_graph_t *g, int from, int to)
{
    if(search_info(g->node[from].neighbors, to) != NULL)  /* edge exists? */
      return(1);
    else
      return(0);
}

/******************* gs_clear_graph() ********************/
/** Removes all edges from graph                        **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_clear_graph(gs_graph_t *g)
{
  int n;
  elem_t *neighb;

  for(n=0; n<g->num_nodes; n++)          /* for all nodes */
  {
    while(g->node[n].neighbors !=0) 
    {                      /* remove all neighbor elements */
      neighb = g->node[n].neighbors;
      g->node[n].neighbors = 
	g->node[n].neighbors->next;
      free(neighb);
    }
  }
}

/******************* gs_clear_graph() ********************/
/** Deletes graph                                       **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_delete_graph(gs_graph_t *g)
{
  gs_clear_graph(g);
  free(g->node);
  free(g);
}

/************************ gs_degree() ********************/
/** Calculates number of neighbors of node              **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**             n: node                                 **/
/** RETURNS:                                            **/
/**     degree                                          **/
/*********************************************************/
int gs_degree(gs_graph_t *g, int n)
{
  int degree;
  elem_t *neighb;

  if(n >= g->num_nodes)
      return(0);
  degree = 0;
  neighb = g->node[n].neighbors;
  while(neighb != NULL)      /* go through all neighbors */
  {
    degree++;
    neighb = neighb->next;
  }
  return(degree);
}


/*********** gs_preferential_attachment() ****************/
/** Generates graph bei "adding" one node after the     **/
/** other. For each "added" node, exactly m edges to    **/
/** already "old added" nodes are inserted randomly. The**/
/** probability that an "old added" nodes receives a new**/
/** edge is proportional to its current degree          **/ 
/** No self loops are allowed. No edge is allowed to    **/
/*+ appear twice!                                       **/
/** PARAMETERS: (*)= return-paramter                    **/
/**         (*) g: graph                                **/
/**             m: number of edges to be added          **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_preferential_attachment(gs_graph_t *g, int m)
{
  int t;
  int n1, n2;
  int *pick;            /* array which holds for each edge {n1,n2} */
                        /* the numbers n1 and n2. Used for picking */
                       /* nodes proportional to its current degree */
  int num_pick;              /* number of entries in 'pick' so far */
  int max_pick;                       /* maximum number of entries */

  if(g->num_nodes < m+1)
  {
      printf("graph too small to have at least %d edges per node!\n", m);
      exit(1);
  }
  max_pick = 2*m*g->num_nodes- m*(m+1);
  pick = (int *) malloc(max_pick*sizeof(int));
  num_pick=0;
  for(n1=0; n1<m+1; n1++) /* start: complete subgraph of m+1 nodes */

    for(n2=n1+1; n2<m+1; n2++)
    {
      gs_insert_edge(g, n1, n2);
      pick[num_pick++] = n1;
      pick[num_pick++] = n2;
    }

  for(n1=m+1; n1<g->num_nodes; n1++)            /* add other nodes */
  {
    t=0;
    while(t<m)                                   /* insert m edges */
    {
      do
        n2 = (int) pick[(int) floor(drand48()*num_pick)];
      while(n2==n1);              /* chose pair of different nodes */
      if(!gs_edge_exists(g, n1, n2))
      {
	gs_insert_edge(g, n1, n2);
	pick[num_pick++] = n1;
	pick[num_pick++] = n2;
	t++;
      }
    }
  }
  free(pick);
}


/******************* gs_write_graph() ********************/
/** prints graph as neighbor lists to 'file'            **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      g: graph                                       **/
/**   file: where to write (e.g. stdout)                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_write_graph(gs_graph_t *g, FILE *file)
{
    int n;

    for(n=0; n<g->num_nodes; n++)
    {
	fprintf(file, "node: %d, neigbors: ", n);
	write_list(g->node[n].neighbors, file);
    }
}


/********************* gs_dot_graph() ********************/
/** prints graph in dot forma to 'file'                 **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      g: graph                                       **/
/**   file: where to write (e.g. stdout)                **/
/**    dir: is graph directed?                          **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_dot_graph(gs_graph_t *g, FILE *file, int dir)
{
    int n;
    elem_t *elem;

    if(dir)
      fprintf(file, "digraph test {\n");
    else
      fprintf(file, "graph test {\n");
    fprintf(file, "node [height=0.2,width=0.2,label=\"\",fixedsize=true]\n");

    for(n=0; n<g->num_nodes; n++)       /* go through all node */
    {
      fprintf(file, "%d\n", n);
      elem = g->node[n].neighbors;
      while(elem != NULL)           /* loop over all neighbors */
      {
	if(dir)
	  fprintf(file, "%d -> %d\n", n, elem->info);
	else
	  if(n <= elem->info)     /* print each pair only once */
	    fprintf(file, "%d -- %d\n", n, elem->info);

	elem = elem->next;                    /* next neighbor */
      }
    }
    fprintf(file, "}\n");
}


/************************ gs_clusters() *********************/
/** Calculates for graph  the connected components:        **/
/** An array is updated, where for each node the id        **/
/** (0,1,...,num_clusters-1) of the cluster it belongs to  **/
/** is stored. Also, an array is created an returend, where**/
/** for each cluster the number of nodes is contains is    **/
/** stored.                                                **/
/** PARAMETERS: (*)= return-paramter                       **/
/**            g: graph                                    **/
/**       (*) id: for each node, id of cluster             **/
/** (*) num_cl_p: (p. to) number of clusters               **/
/** RETURNS:                                               **/
/**     array with sizes of each cluster (created)         **/
/************************************************************/
int *gs_clusters(gs_graph_t *g, int *id, int *num_cl_p)
{
  int *cands;               /* 'stack' for nodes yet to be considered */
  int cands_top;                              /* top entry of 'stack' */
  int num_cl;                                   /* number of clusters */
  int *size;                                   /* ... of each cluster */
  elem_t *neighb;
  int i, k, cl;                          /* loop counters, nodes, ... */

  cands = (int *) malloc(g->num_nodes*sizeof(int));
  for(i=0; i<g->num_nodes; i++)
    id[i] = -1;            /* means: node has not been visited so far */

  num_cl = -1;
  for(i=0; i<g->num_nodes; i++)                    /* visit all nodes */
    if(id[i] == -1)                            /* start new cluster ? */
    {
      num_cl++;
      id[i] = num_cl;
      cands[0] = i;                              /* put node on stack */
      cands_top = 0;
      while(cands_top > -1)    /* while there are candidates on stack */
      {
	k = cands[cands_top--];
	neighb = g->node[k].neighbors;
	while(neighb != 0)                 /* loop over all neighbors */
	{
	  if(id[neighb->info] == -1)          /* not yet considered ? */
	  {
	    id[neighb->info] = num_cl;             /* join to cluster */
	    cands[++cands_top] = neighb->info;        /* put on stack */
	  }
	  neighb = neighb -> next;
	}
      }
    }

  num_cl++;                                     /* number of clusters */
  *num_cl_p = num_cl;
  size = (int *) malloc(num_cl*sizeof(int));
  for(cl=0; cl<num_cl; cl++)  
    size[cl] = 0;
  for(i=0; i<g->num_nodes; i++)            /* determine cluster sizes */
    size[id[i]]++;

  free(cands);
  return(size);
}
