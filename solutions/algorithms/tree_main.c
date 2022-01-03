/*******************************************************************/
/*** Implementation of binary search trees                       ***/
/*** Main function                                               ***/
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

int main(int argc, char *argv[])
{
  node_t *tree, *node, *node2;
  int value, in;

  tree = NULL;
  node = create_node(20);
  tree = insert_node(tree, node, &in);
  node = create_node(30);
  tree = insert_node(tree, node, &in);
  node = create_node(5);
  tree = insert_node(tree, node, &in);
  node = create_node(15);
  tree = insert_node(tree, node, &in);
  node = create_node(25);
  tree = insert_node(tree, node, &in);
  node = create_node(35);
  tree = insert_node(tree, node, &in);
  node = create_node(3);
  tree = insert_node(tree, node, &in);
  node = create_node(12);
  tree = insert_node(tree, node, &in);
  node = create_node(27);
  tree = insert_node(tree, node, &in);
  node = create_node(40);
  tree = insert_node(tree, node, &in);
  print_tree(tree); printf("\n");

  /** uncomment this, if you want to test finding of nodes **/
  /*value = 22;
  if(find_node(tree, value) != NULL)
    printf("key %d is contained in tree.\n", value);
  else
    printf("key %d is NOT contained in tree.\n", value);
  value = 25;
  if(find_node(tree, value) != NULL)
    printf("key %d is contained in tree.\n", value);
  else
  printf("key %d is NOT contained in tree.\n", value);*/

  /** uncomment this, if you want to test removal of nodes **/
  /*tree = remove_node(tree, 35, &node);
  printf("removed: %d\n", node->key);
  print_tree(tree); printf("\n");*/


  return(0);
}
