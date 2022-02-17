/*******************************************************************/
/*** Implementation of binary search trees                       ***/
/*** Header file                                                 ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Trees                                              ***/
/*******************************************************************/


#ifndef _TREE_H_
#define _TREE_H_

/* data structures for tree elements */
struct node_struct
{
    int                   key;                              /* holds key */
    struct node_struct  *left;  /* points to left subtree (NULL if none) */
    struct node_struct *right; /* points to right subtree (NULL if none) */
};

typedef struct node_struct node_t;       /* define new type for nodes */

/** function prototypes */

extern node_t *create_node(int value);
extern int delete_node(node_t *node);
extern node_t *insert_node(node_t *tree, node_t *node, int *in_p);
extern void print_tree(node_t *tree);
extern node_t *remove_node(node_t *tree, int key_rem, node_t **node_p);
extern node_t *find_node(node_t *tree, int key);

#endif  /* ifndef _TREE_H_ */
