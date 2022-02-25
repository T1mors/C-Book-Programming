/**************************************************************************/
/*** Data structures and functions for binary search trees              ***/
/*** Course: introduction to computational physics                      ***/
/***                                                                    ***/ 
/*** (c) February 2022  A.K. Hartmann, University of Oldenburg, Germany ***/
/**************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>




/* data structures for tree elements */
struct node_struct
{
    int                  info;                  /* holds ``information'' */
    struct node_struct  *left;  /* points to left subtree (NULL if none) */
    struct node_struct *right;  /* points to left subtree (NULL if none) */
};

typedef struct node_struct node_t;       /* define new type for nodes */

/* function commentary header (empty): */

/*******************  *****************/
/**  **/
/** PARAMETERS: (*)= return-paramter         **/
/**  **/
/** RETURNS:                               **/
/**  **/
/******************************************/


/* function commentary header (empty): */

/******************* create_node() ********************/
/** Creates an tree node and initializes info        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        value: of info                            **/
/** RETURNS:                                         **/
/**     pointer to new node                          **/
/******************************************************/
node_t *create_node(int value)
{
  node_t *node;

  node = (node_t *) malloc (sizeof(node_t));
  node->info = value;
  node->right = NULL;
  node->left = NULL;
  return(node);
}

/********************* delete_node() ******************/
/** Deletes a single tree node (i.e. only if it      **/
/** is not linked to other nodes)                    **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         node: pointer to node                    **/
/** RETURNS:                                         **/
/**    0: OK, 1: error                               **/
/******************************************************/
int delete_node(node_t *node)
{
  if(node == NULL)
  {
    fprintf(stderr, "attempt to delete `nothing`\n");
    return(1);
  }
  else if( (node->left != NULL)||(node->right != NULL))
  {
    fprintf(stderr, "attempt to delete linked node!\n");
    return(1);
  }
  else
  {
    free(node);
    return(0);
  }
}

/********************* insert_node() ******************/
/** Inserts 'node' into the 'tree' such that the     **/
/** increasing order is preserved                    **/
/** if node exists already, nothing happens          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**         node: pointer to node                    **/
/** RETURNS:                                         **/
/**   (new) pointer to root of tree                  **/
/******************************************************/
node_t *insert_node(node_t *tree, node_t *node)
{
  node_t *current;

  if(tree==NULL)
    return(node);
  current = tree;
  while( current != NULL)                  /* run through tree */
  {
    if(current->info==node->info)  /* node already contained ? */
      return(tree);
    if( node->info < current->info)            /* left subtree */  
    {
      if(current->left == NULL)
      {             
	current->left = node;                      /* add node */
	return(tree);
      }
      else
	current = current->left;         /* continue searching */
    }
    else                                      /* right subtree */
    {
      if(current->right == NULL)             
      {
	current->right = node;                     /* add node */
	return(tree);
      }
      else
	current = current->right;         /* continue searching */
    }
  }
  return(tree);
}

/********************* print_tree() *******************/
/** Prints tree in ascending order recursively.      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   nothing                                        **/
/******************************************************/
void print_tree(node_t *tree)
{
  if(tree != NULL)
  {
    print_tree(tree->left);
    printf("%d ", tree->info);
    print_tree(tree->right);
  }
}

/************** print_tree_indent() *******************/
/** Prints tree in ascending order recursively.      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   nothing                                        **/
/******************************************************/
void print_tree_indent(node_t *tree, int level)
{
  int t;
  if(tree != NULL)
  {
    print_tree_indent(tree->left, level+1);
    for(t=0; t<level; t++)
      printf("  ");
    printf("%d\n", tree->info);
    print_tree_indent(tree->right, level+1);
  }
}


/******************** remove_value() ******************/
/** Removes node containung the 'value' from  the    **/
/** tree  (leaves left,right pointer of removed      **/
/** nodes as they are).                              **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**         value: to be removed                     **/
/**    (*) node_p: address of ptr to removed node    **/
/** RETURNS:                                         **/
/** (new) pointer to the root                        **/
/******************************************************/
node_t *remove_value(node_t *tree, int value, node_t **node_p)
{
  node_t *current;                     /* used for running through tree */
  node_t  *pred;           /* always pred->(left/right) = current holds */
  pred = NULL;
  current = tree;
  while( (current != NULL)&&(current->info != value) )  /* search value */
  {
    pred = current;
    if(current->info > value)
      current = current->left;
    else
      current = current->right;
  }

  if(current == NULL)                              /* value not found ? */
  {
    *node_p = NULL;
    return(tree);
  }

  if( (current->left != NULL)&&(current->right != NULL))   /* 2 desc. ? */
  {
    node_t *current2;
    int info2;
    current2 = current;
    pred = current;
    current = current->right;  /* search smallest val. in right subtree */
    while( current->left != NULL)
    {
      pred = current;
      current = current->left;
    }
    info2 = current2->info;                          /* exchange values */
    current2->info = current->info;
    current->info = info2;
  }
  *node_p = current;
  /* now node 'current' is removed from tree. We know here that it */
  /* has at most one descendant                                    */

  /** (in principle) MISSING: set left/right of removed node to NULL **/
  if(pred == NULL)                              /* deleted node is root */
  {
    if( (current->left == NULL)&&(current->right==NULL))
      return(NULL);                                   /* tree now empty */
    else if( current->right != NULL) 
      return(current->right);
    else
      return(current->left);
  }
  else             /* deleted node is not root -> has predcessor 'pred' */
  {
    if(pred->left == current)
    {
      if( (current->left == NULL)&&(current->right==NULL))
	pred->left = NULL;
      else if( current->right != NULL) 
	pred->left = current->right;
      else
	pred->left = current->left;
    }
    else
    {
      if( (current->left == NULL)&&(current->right==NULL))
	pred->right = NULL;
      else if( current->right != NULL) 
	pred->right = current->right;
      else
	pred->right = current->left;
    }
  }

  return(tree);
}




/********************* tree_height() ******************/
/** Calculates height of tree  recursively.          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   height of tree                                 **/
/******************************************************/
int tree_height(node_t *tree)
{
  int left_height, right_height;

  /** ADD YOU CODE HERE **/

  /** 0 SHOULD BE RETURNED FOR AN EMPTY TREE: **/

  if (tree == NULL){
    return (0);
  }

  left_height = tree_height(tree->left) + 1;
  right_height = tree_height(tree->right) + 1;

  if (left_height < right_height){
    return (right_height);
  }
  else{
    return (left_height);
  }

}





/**************** tree_exchange() **********************/
/** Permutes array by peforming 'num_ex' exchanges   **/
/** of randomly selected pairs.                      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**           a: array                               **/
/**        size: ... of array                        **/
/**      num_ex: number of pairs which are exchanged **/
/** RETURNS:                                         **/
/**   (nothing)                                      **/
/******************************************************/
void tree_exchange(int *a, int size, int num_ex)
{
  int ex;                                               /* loop counter */
  int t1, t2;                                          /* array indices */
  int tmp;                             /* temporary value for exchanges */


  /** ADD CODE FOR PERFORMING EXCHANGES HERE. USE: **/

  for (ex = 0; ex < num_ex; ex++)
  {
    t1 =  (int) floor(size*drand48());  /* select 1st index of a pair */
    t2 =  (int) floor(size*drand48()); /* selcet 2nd index of a pair */

    tmp = a[t1];
    a[t1] = a[t2];
    a[t2] = tmp;
  }  

}




int main(int argc, char *argv[])
{
  node_t *tree, *node;                                /* root and any node */
  double height;                         /* for average of estimate of height */
  int t;                                                   /* loop counter */
  int *a;                                         /* array for permutation */
  int size;                                               /* size of array */

  size = atoi(argv[1]);                    /* read input from command line */
  a = (int *) malloc(size*sizeof(int));

  for (t = 0; t < size; t++){
    a[t] = (int) floor(10*size*drand48());
  }
  tree = NULL;                                     /* put into sorted stree */
  for(t=0; t<size; t++)
  {
    node = create_node(a[t]);
    tree = insert_node(tree, node);
  }
  print_tree_indent(tree, 0);
  printf("\n");
  height = tree_height(tree);                     /* statistics of heights */
  for(t=size-1; t>=0; t--)                                /* delete tree */
  {
    tree = remove_value(tree, a[t], &node);
    delete_node(node);
  }
  
  printf("array a:\n");
  for (t = 0; t < size; t++){
    printf("%d ", a[t]);
  }

  printf("\n");
  	
  printf("height: %f\n", height);

  free(a);
  return(0);
}
