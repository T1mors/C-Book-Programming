/*******************************************************************/
/*** Implementation of binary search trees                       ***/
/*** Function for removing an element having a given key value   ***/
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

/*********************** remove_node() ****************/
/** Removes node containung the 'key_rem' from  the  **/
/** tree.                                            **/
/** If the 'key' is not contained in the tree,       **/
/** nothing happens.                                 **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**      key_rem: to be removed                      **/
/**   (*) node_p: address of ptr to removed node     **/
/*+               (NULL if not found)                **/
/** RETURNS:                                         **/
/** (new) pointer to the root                        **/
/******************************************************/
node_t *remove_node(node_t *tree, int key_rem, node_t **node_p)
{
  node_t *del_node;
  node_t *current;                     /* used for running through tree */
  node_t  *pred;           /* always pred->(left/right) = current holds */
  pred = NULL;
  current = tree;
  while( (current != NULL)&&(current->key != key_rem) )   /* search key */
  {
    pred = current;
    if(current->key > key_rem)
      current = current->left;
    else
      current = current->right;
  }

  if(current == NULL)                                /* key not found ? */
  {
    *node_p = NULL;
    return(tree);
  }

  if( (current->left != NULL)&&(current->right != NULL))   /* 2 desc. ? */
  {
    node_t *current2;
    int key2;
    current2 = current;
    pred = current;
    current = current->right;  /* search smallest val. in right subtree */
    while( current->left != NULL)
    {
      pred = current;
      current = current->left;
    }
    key2 = current2->key;                              /* exchange keys */
    current2->key = current->key;
    current->key = key2;
  }
  *node_p = current;
  /* now node 'current' is removed from tree. We know here that it */
  /* has at most one descendant                                    */
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

