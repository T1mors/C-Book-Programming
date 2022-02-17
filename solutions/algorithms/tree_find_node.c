/*******************************************************************/
/*** Implementation of binary search trees                       ***/
/*** Function for looking for a key value in the tree            ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Trees                                              ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/*********************** find_node() ******************/
/** Locates a node with a given 'key' in a tree.     **/
/** If the 'key' is not contained in the tree,       **/
/** NULL is returned                                 **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**          key: to be located                      **/
/** RETURNS:                                         **/
/** pointer to node (NULL if key is not exisiting)   **/
/******************************************************/
node_t *find_node(node_t *tree, int key)
{
  node_t *current;

  current = tree;
  while(current != NULL)                   /* run through tree */
  {
    if(key==current->key)                   /* key contained ? */
      return(current);
    if(key < current->key)                     /* left subtree */  
	current = current->left;         /* continue searching */
    else                                      /* right subtree */
	current = current->right;        /* continue searching */
  }
  return(NULL);
}





