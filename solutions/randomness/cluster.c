/*******************************************************************/
/*** Performs cluster analysis (k-means,hierarchical clustering  ***/
/*** for sets of data vectors                                    ***/
/*** COMPILE:                                                    ***/
/*** cc -o cluster cluster.c -lgsl -lgslcblas -lm -Wall          ***/
/***    -I../algorithms  ../algorithms/graphs.c                  ***/
/***     ../algorithms/list.c ../algorithms/graph_comps.c         ***/
/*** Sameple from the book:                                      ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2014 (2nd edition)              ***/
/***                                                             ***/
/*** Chapter: Randomness and statistics                          ***/
/*** Section: Clustering                                         ***/
/*******************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include "graphs.h"

typedef struct cluster_node
{ 
  int ID;     /* ID of cluster */
  int size;   /* number of members */
  double dist;  /* distance of sub clusters */
  struct cluster_node *left; /* sub cluster */
  struct cluster_node *right; /* sub cluster */
} cluster_node_t;
  

/************* cluster_test_data1() ********************/
/** Generate 'num_points' vectors of random data      **/
/** centered about three centered                     **/
/** each vector has 'dim' components                  **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**         dim: size of vectors                      **/
/**  num_points: number of vectors                    **/
/**                                                   **/
/** Returns:                                          **/
/**    matrix containing the vectors (=columns)       **/
/*******************************************************/
gsl_matrix *cluster_test_data1(int dim, int num_points)
{
  gsl_matrix *data;          /* matrix containing random vectors */
  int t, d;                                     /* loop counters */
  gsl_rng *r;                         /* random number generator */
  double randnum;                      /* Gaussian random number */
  int do_print = 0;                             /* print vectors */

  data = gsl_matrix_alloc(dim, num_points);
  r = gsl_rng_alloc(gsl_rng_mt19937);

  for(t=0; t<num_points; t++)                 /* generate points */
  {
    randnum = gsl_rng_uniform(r);               /* choose center */
    if(randnum < 0.2)
      for(d=0; d<dim; d++)
	gsl_matrix_set(data, d, t, 0);
    else if(randnum <0.5)
      for(d=0; d<dim; d++)
	gsl_matrix_set(data, d, t, 1.0);
    else
      for(d=0; d<dim; d++)
	gsl_matrix_set(data, d, t, 1.0-d);


    for(d=0; d<dim; d++)                  /* add Gaussianm noise */
    {
      randnum = gsl_ran_gaussian(r, 1.0);     
      gsl_matrix_set(data, d, t,
     	     gsl_matrix_get(data, d, t)+0.1*randnum  );
    }
  }

  if(do_print)
    for(t=0; t<num_points; t++)               /* generate points */
    {
      for(d=0; d<dim; d++)
	printf("%f ", gsl_matrix_get(data, d, t));
      printf("\n");
    }


  gsl_rng_free(r);

  return(data);
}

/************* cluster_test_data1() ********************/
/** Generate 'num_points' vectors of random data      **/
/** organized in planar rings                         **/
/** each vector has 'dim' components                  **/
/**                                                   **/
/** Parameters: (*) = return parameter                **/
/**         dim: size of vectors                      **/
/**  num_points: number of vectors                    **/
/**                                                   **/
/** Returns:                                          **/
/**    matrix containing the vectors (=columns)       **/
/*******************************************************/
gsl_matrix *cluster_test_data2(int dim, int num_points)
{
  gsl_matrix *data;          /* matrix containing random vectors */
  int t, d;                                     /* loop counters */
  gsl_rng *r;                         /* random number generator */
  double randnum;                      /* Gaussian random number */
  int do_print = 0;                             /* print vectors */
  double radius, angle;  

  data = gsl_matrix_alloc(dim, num_points);
  r = gsl_rng_alloc(gsl_rng_mt19937);

  for(t=0; t<num_points; t++)                 /* generate points */
  {
    randnum = gsl_rng_uniform(r);            /* inner/outer ring */
    if(randnum < 0.2)
      radius = 0;
    else
      radius = 1;
    radius += 0.4* gsl_rng_uniform(r);     /* add random offset */
    if(radius <0)
      radius = 0;
    angle = 2*M_PI*gsl_rng_uniform(r);          /* choose angle */
    gsl_matrix_set(data, 0, t, radius*cos(angle));    /* vector */
    gsl_matrix_set(data, 1, t, radius*sin(angle));
    for(d=2; d<dim; d++)
	gsl_matrix_set(data, d, t, 0);
  }

  if(do_print)
    for(t=0; t<num_points; t++)               /* generate points */
    {
      for(d=0; d<dim; d++)
	printf("%f ", gsl_matrix_get(data, d, t));
      printf("\n");
    }


  gsl_rng_free(r);

  return(data);
}


/****************** cluster_k_means() *****************/
/** For a set of 'data' points, perform k-means      **/
/** clustering: calculate k "centers" such that each **/
/** data point is assigned to its closest center and **/
/** each center is the average of the assigned data  **/
/** The initial assignment is random using 'rng'.    **/      
/** PARAMETERS: (*)= return-paramter                 **/
/**         data: data vectors (columns of matrix)   **/
/**            k: number of clusters                 **/
/**          rng: random number generator            **/   
/** (*) spread_p: (ptr to) final spread              **/
/** RETURNS:                                         **/
/**     array of cluster IDs                         **/
/******************************************************/
int *cluster_k_means(gsl_matrix *data, int k, gsl_rng *rng, double *spread_p)
{
  int *cluster;             /* holds for each point its cluster ID */
  gsl_matrix *center;         /* holds for each cluster its center */
  int *cluster_size;         /* holds for each cluster its #points */
  int dim;           /* number of components of data point vectors */
  int num_points;                         /* number of data points */
  int t, d, c;                                    /* loop counters */
  double spread, spread_old;          /* total distance to centers */
  double dist, dist_min;   /* (minimum) dist. between point/center */
  double diff;            /* lateral distance between point/center */
  int c_min;                 /* center which is closest to a point */
  int do_print = 0;                               /* for debugging */

  num_points = data->size2;                          /* initialize */
  dim = data->size1;
  cluster = (int *) malloc(num_points*sizeof(int));
  cluster_size = (int *) malloc(k*sizeof(int));
  center = gsl_matrix_alloc(dim, k);

  for(t=0; t<num_points; t++)    /* intial assignments to clusters */
    cluster[t] = (int) k*gsl_rng_uniform(rng);

  spread = 1e100;
  spread_old = 2e100;
  while ( (spread_old-spread)>0.01*spread_old)        /* main loop */
  {
    gsl_matrix_set_all(center, 0.0);
    for(c=0; c<k; c++)
      cluster_size[c] = 0;
    for(t=0; t<num_points; t++)               /* determine centers */
    {
      cluster_size[cluster[t]]++;
      for(d=0; d<dim; d++)
	gsl_matrix_set(center, d, cluster[t], 
		       gsl_matrix_get(center, d, cluster[t])+
		       gsl_matrix_get(data, d, t));
    }  
    for(c=0; c<k; c++)
      if(cluster_size[c] > 0)
      for(d=0; d<dim; d++)
	gsl_matrix_set(center, d, c, 
		       gsl_matrix_get(center, d, c)/cluster_size[c]);
    if(do_print)
    {
      for(d=0; d<dim; d++)
	printf("%f ", gsl_matrix_get(center, d, 2));
      printf("\n");
    }

    spread_old = spread;
    spread = 0;
    for(t=0; t<num_points; t++)        /* determine closest center */
    {
      c_min = -1;
      for(c=0; c<k; c++)                  /* test with all centers */
      {
	dist = 0;               /* calculate distance point/center */
	for(d=0; d<dim; d++)
	{  
	  diff = gsl_matrix_get(center, d, c)-gsl_matrix_get(data, d, t);
	  dist += diff*diff;
	}
	if( (c_min == -1)||(dist_min > dist))  /* closest center ? */
	{
	  c_min = c;
	  dist_min = dist;
	}
      }
      cluster[t] = c_min;
      spread += dist_min;
    }
  }

  *spread_p = spread;
  gsl_matrix_free(center);
  free(cluster_size);
  return(cluster);
}

/**************** cluster_distances() *****************/
/** For a set of 'data' points, calculate the pair-  **/
/** wise (Eucledian) distance matrix                 **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        data: data vectors (columns of matrix)    **/
/** RETURNS:                                         **/
/**     distance matrix                              **/
/******************************************************/
gsl_matrix *cluster_distances(gsl_matrix *data)
{
  gsl_matrix *dist;               /* matrix containing distances */
  int dim;         /* number of components of data point vectors */
  int num_points;                       /* number of data points */
  int t1, t2, d;                                /* loop counters */
  double distance, diff;         /* auxiliary distance variables */

  dim = data->size1;
  num_points = data->size2;                        /* initialize */
  dist = gsl_matrix_alloc(num_points, num_points);

  for(t1=0; t1<num_points; t1++)       /* iterate over all pairs */
    for(t2=0; t2<=t1; t2++) 
    {
      distance = 0;
      for(d=0; d<dim; d++)                 /* calculate distance */
      {
	diff = gsl_matrix_get(data, d, t1) - gsl_matrix_get(data, d, t2);
	distance += diff*diff;
      }
      gsl_matrix_set(dist, t1, t2, sqrt(distance));       /* set */
      gsl_matrix_set(dist, t2, t1, gsl_matrix_get(dist, t1, t2));
    }

  return(dist);
}

/********** cluster_threshold_graph() *****************/
/** For a set of points with pairwise 'distance'     **/
/** matrix, set up graph which includes edges for    **/
/** all points which are less the 'threshold' apart. **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        distance: pairwise distances              **/
/** RETURNS:                                         **/
/**     distance matrix                              **/
/******************************************************/
gs_graph_t *cluster_threshold_graph(gsl_matrix *distance, double threshold)
{
  gs_graph_t *g;
  int num_nodes;
  int n1, n2;                                 /* node counter */

  num_nodes = distance->size1;
  if(num_nodes != distance->size2)
  {
    fprintf(stderr, "Distance matrix is not a square matrix\n");
    exit(1);
  }

  g = gs_create_graph(num_nodes);

  for(n1=0; n1<num_nodes; n1++)       /* loop over all pairs of nodes */
    for(n2=n1+1; n2<num_nodes; n2++)
      if(gsl_matrix_get(distance, n1, n2) < threshold)  /* insert edge ? */
	gs_insert_edge(g, n1, n2);                

  return(g);
}

/**************** cluster_print_edges() ******************/
/** prints graph edhes to 'file'. Node positions        **/
/**  are taken from first two entries of 'data'         **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      g: graph                                       **/
/**   file: where to write (e.g. stdout)                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void cluster_print_edges(gs_graph_t *g, gsl_matrix *data, FILE *file)
{
    int n;
    elem_t *elem;

    for(n=0; n<g->num_nodes; n++)      /* go through all nodes */
    {
      elem = g->node[n].neighbors;
      while(elem != NULL)           /* loop over all neighbors */
      {
	if(n <= elem->info)       /* print each pair only once */
	{
	  fprintf(file, "%f %f\n", gsl_matrix_get(data,0,n), 
		  gsl_matrix_get(data,1,n));
	  fprintf(file, "%f %f\n\n", gsl_matrix_get(data,0,elem->info), 
		  gsl_matrix_get(data,1,elem->info));
	}
	elem = elem->next;                    /* next neighbor */
      }
    }
}


/**************** cluster_print_tree() *******************/
/** prints tree to 'file' (uses pairs of (x,y) points   **/
/** and gnuplot multiset modus to plot many segments    **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      tree: tree to be printed                       **/
/**  x_offset: shift of tree to the right               **/
/**   y_level: y position of father node                **/
/**      file: where to write (e.g. stdout)             **/
/** RETURNS:                                            **/
/**     x_pos (of the root of the tree)                 **/
/*********************************************************/
double cluster_print_tree(cluster_node_t *tree, double x_offset, 
			  double y_level, FILE *file)
{
  double x_left, x_right, x_root;

  if( (tree->left==NULL) || (tree->right==NULL))       /* leaf ? */
  {                                          /* draw one line up */
    fprintf(file, "%f %f\n%f %f\n\n", x_offset, 0.0, x_offset, y_level);
    return(x_offset);
  }
  else                               /* inner node: lines horizontal + up  */
  {
    x_left = cluster_print_tree(tree->left, x_offset, tree->dist, file);
    x_right = cluster_print_tree(tree->right, x_offset+tree->left->size, 
				 tree->dist, file);
    fprintf(file, "%f %f\n%f %f\n\n", x_left, tree->dist, 
	                              x_right, tree->dist);
    x_root = (x_left + x_right)/2;
    fprintf(file, "%f %f\n%f %f\n\n", x_root, tree->dist, 
	                              x_root, y_level);
    return(x_root);
  }
}


/************ cluster_agglomerative() *****************/
/** For a set of points with pairwise 'distance'     **/
/** matrix, perform agglomerative clustering         **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        distance: pairwise distances              **/
/** RETURNS:                                         **/
/**     tree representing structure (dendrogram)     **/
/******************************************************/
cluster_node_t *cluster_agglomerative(gsl_matrix *distance)
{
  cluster_node_t *tree;                     /* root of dendrogram */
  cluster_node_t *node;                    /* nodes of dendrogram */
  int num_points;             /* number of points to be clustered */
  int num_clusters;                 /* current number of clusters */
  int next_ID;                              /* ID of next cluster */
  int ID_curr;                           /* ID of current cluster */
  int ID_min1, ID_min2;    /* IDs of clusters having min distance */
  int last_ID;                /* ID of cluster in last row/column */ 
  int entry_min1, entry_min2;       /* entry  having min distance */
  int c1, c2;                                    /* loop counters */
  int *pos;             /* position of cluster in distance matrix */
  int *cluster; /* ID of cluster in each row/colum, inv. of 'pos' */
  double delta;                             /* auxiliary distance */

  num_points = distance->size1;
  if(num_points != distance->size2)
  {
    fprintf(stderr, "Distance matrix is not a square matrix\n");
    exit(1);
  }

  /*for(c1=0; c1<num_points; c1++)
    for(c2=0; c2<num_points; c2++)
    printf("d(%d,%d)=%f\n", c1, c2, gsl_matrix_get(distance, c1, c2));*/

  cluster = (int *) malloc(num_points*sizeof(int));
  pos = (int *) malloc( (2*num_points-1)*sizeof(int));
  node = (cluster_node_t *) 
         malloc( (2*num_points-1)*sizeof(cluster_node_t));

  for(c1=0; c1<num_points; c1++)                    /* initalize  */
  {
    pos[c1] = c1;
    cluster[c1] = c1;
    node[c1].left = NULL;
    node[c1].right = NULL;
    node[c1].dist = 0.0;
    node[c1].ID = c1;
    node[c1].size = 1;
  }

  num_clusters = num_points;
  next_ID = num_clusters;
  while(num_clusters > 1)        /* until all clusters are merged */
  {
    entry_min1=0; entry_min2=1;  /* search min. off-diag distance */
    for(c1=0; c1<num_clusters; c1++)
      for(c2=c1+1; c2<num_clusters; c2++)
	if(gsl_matrix_get(distance, c1, c2) < 
	   gsl_matrix_get(distance, entry_min1, entry_min2))
	{
	  entry_min1=c1, entry_min2=c2;
	}


    ID_min1 = cluster[entry_min1];       /* determine cluster IDs */
    ID_min2 = cluster[entry_min2];
    
    /*printf("# %d %d at min=%f\n", ID_min1, ID_min2,
      gsl_matrix_get(distance, entry_min1, entry_min2));*/

    node[next_ID].left = &(node[ID_min1]);        /* merge clusters */
    node[next_ID].right = &(node[ID_min2]);
    node[next_ID].ID = next_ID;
    node[next_ID].size = node[ID_min1].size + node[ID_min2].size;
    node[next_ID].dist = 
      gsl_matrix_get(distance, entry_min1, entry_min2);


    for(c1=0; c1<num_clusters; c1++)  /* distances to new cluster */
      if(c1 == entry_min1)
	gsl_matrix_set(distance, entry_min1, c1, 0);
      else if(c1 != entry_min2)
      {
	ID_curr = cluster[c1];
	delta = node[ID_min1].size* 
	  gsl_matrix_get(distance, entry_min1, c1)+	  
	  node[ID_min2].size*
	  gsl_matrix_get(distance, entry_min2, c1);
	delta /= node[next_ID].size;
	gsl_matrix_set(distance, entry_min1, c1, delta);
	gsl_matrix_set(distance, c1, entry_min1, delta);
      }

    num_clusters--;
    if(num_clusters == 1)
      tree = &(node[next_ID]);                   /* set root of tree */
    last_ID = cluster[num_clusters];/* last cluster -> entry_min2 */
    pos[last_ID] = entry_min2;
    cluster[entry_min2] = last_ID;
    gsl_matrix_swap_rows(distance, num_clusters, entry_min2);
    gsl_matrix_swap_columns(distance, num_clusters, entry_min2);

    cluster[entry_min1] = next_ID;
    pos[next_ID] = entry_min1;
    next_ID++;
	   
  }

  free(pos);                                          /* clean up */
  free(cluster);

  return(tree);
}

/***************** cluster_list_tree() *******************/
/** prints sets of clusters in tree to 'file'. All nodes**/
/** where the (avg.) distance is below 'threshold' are  **/
/** considered to be in one cluster                     **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      tree: tree to be printed                       **/
/** threshold: below which nodes are in one cluster     **/
/**      data: entries 0 and 1 used as x,y coordinates  **/
/**      file: where to write (e.g. stdout)             **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void cluster_list_tree(cluster_node_t *tree, double threshold, 
		       gsl_matrix *data, FILE *file)
{
  if( (tree->left == NULL)&&(tree->right == NULL) )
  {
    fprintf(file, "%f %f\n", gsl_matrix_get(data, 0, tree->ID),
	    gsl_matrix_get(data, 1, tree->ID));
    return;
  }
  cluster_list_tree(tree->left, threshold, data, file);
  if( (tree->dist > threshold) && (tree->left->dist < threshold))
    fprintf(file, "\n\n");    /* finish one cluster */
  cluster_list_tree(tree->right, threshold, data, file);
  if( (tree->dist > threshold) && (tree->right->dist < threshold))
    fprintf(file, "\n\n");    /* finish one cluster */
}


/********************** main program         *********************/
int main(int argc, char *argv[])
{
  int dim = 2;         /* number of components of random vectors */
  int t, d, c;                                  /* loop counters */
  int num_points;                           /* number of vectors */
  gsl_matrix *data;                /* random vectors, row by row */
  int *cluster;               /* cluster IDs for each data point */
  int k;                                   /* number of clusters */
  double spread;   /* total spread of data points for clustering */
  gsl_rng *r;                         /* random number generator */
  gsl_matrix *distance;                    /* pairwise distances */
  gs_graph_t *g;                                        /* graph */
  double threshold;       /* for distance to form edges in graph */
  cluster_node_t *tree;                            /* dendrogram */
  int num_comps;                         /* number of components */
  int do_print = 1;                             /* for debugging */
  int method;               /* which clustering method is used ? */

  num_points = 200;
  /*data = cluster_test_data1(dim, num_points);*/
  data = cluster_test_data2(dim, num_points);
  method = 3;


  if(method == 1)    /* k -means ? */
  {
    k = 2;

    if(argc > 1)
      k = atoi(argv[1]);
    
    r = gsl_rng_alloc(gsl_rng_mt19937);
  
    for(t=0; t<10; t++)
    {
      gsl_rng_set(r, 1000+t);
      cluster = cluster_k_means(data, k, r, &spread);
      printf("# k: %d spread: %f\n", k, spread);

      if(do_print)
	for(c=0; c<k; c++)
        {
	  for(t=0; t<num_points; t++)
	    if(cluster[t] == c)
	      {
		for(d=0; d<dim; d++)
		  printf("%f ", gsl_matrix_get(data, d, t));
		printf("\n");
	      }
	  printf("\n\n");
	}
      free(cluster);
    }
  }

  if(method == 2)    /* distance based components ? */
  {
    cluster = (int *) malloc(num_points*sizeof(int));
    threshold = 0.3;
    if(argc > 1)
      sscanf(argv[1], "%lf", &threshold); 
    distance = cluster_distances(data);
    g = cluster_threshold_graph(distance, threshold);
    num_comps = gs_components(g, cluster);

    /*cluster_print_edges(g, data, stdout);*/  
    if(do_print)
    {
      printf("# %d clusters\n", num_comps);
      for(c=0; c<num_comps; c++)
      {
	for(t=0; t<num_points; t++)
	  if(cluster[t] == c)
	  {
	    for(d=0; d<dim; d++)
	      printf("%f ", gsl_matrix_get(data, d, t));
	    printf("\n");
	  }
	printf("\n\n");
      }
    }
    free(cluster);
  gsl_matrix_free(distance);
  }
  if(method == 3)                        /* agglomerative */
  {
    threshold = 1.4;
    if(argc > 1)
      sscanf(argv[1], "%lf", &threshold);
    distance = cluster_distances(data);
    tree = cluster_agglomerative(distance);
    if(argc == 1)
      cluster_print_tree(tree, 0, 1.1*tree->dist, stdout);
    else
      cluster_list_tree(tree, threshold, data, stdout); 
    gsl_matrix_free(distance);
  }

  return(0);
}


