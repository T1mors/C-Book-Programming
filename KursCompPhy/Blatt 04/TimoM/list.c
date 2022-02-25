/*******************************************************************/
/*** Implementation of single-linked lists                       ***/
/*** Basic functions                                             ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Lists                                              ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

elem_t *list_last(elem_t *list)
{
  elem_t *last;
  while (list != NULL) /* run through list */
  {
    last = list;
    list = list->next;
  }
  return (last);
}

/******************* create_element() *****************/
/** Creates an list element an initialized info      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        value: of info                            **/
/** RETURNS:                                         **/
/**     pointer to new element                       **/
/******************************************************/
elem_t *create_element(int value)
{
  elem_t *elem;

  elem = (elem_t *)malloc(sizeof(elem_t));
  elem->info = value;
  elem->next = NULL;
  return (elem);
}

/******************* delete_element() *****************/
/** Deletes a single list element (i.e. only if it   **/
/** is not linked to another element)                **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         elem: pointer to element                 **/
/** RETURNS:                                         **/
/**    0: OK, 1: error                               **/
/******************************************************/
int delete_element(elem_t *elem)
{
  if (elem == NULL)
  {
    fprintf(stderr, "attempt to delete `nothing`\n");
    return (1);
  }
  else if (elem->next != NULL)
  {
    fprintf(stderr, "attempt to delete linked element!\n");
    return (1);
  }
  else
  {
    free(elem);
    return (0);
  }
}

/******************* insert_element() *****************/
/** Inserts the element `elem` in the `list          **/
/** BEHIND the `where`. If 'where' is equal to NULL  **/
/** then the element is inserted at the beginning of **/
/** the list.                                        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         list: first element of list              **/
/**         elem: pointer to element to be inserted  **/
/**        where: position of new element            **/
/** RETURNS:                                         **/
/**  (new) pointer to the beginning of the list      **/
/******************************************************/
elem_t *insert_element(elem_t *list, elem_t *elem, elem_t *where)
{
  if (where == NULL) /* insert at beginning ? */
  {
    elem->next = list;
    list = elem;
  }
  else /* insert elsewhere */
  {
    elem->next = where->next;
    where->next = elem;
  }
  return (list);
}

/******************* print_list() *****************/
/** Prints all elements of a list                **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/** RETURNS:                                     **/
/**          nothing                             **/
/**************************************************/
void print_list(elem_t *list)
{
  while (list != NULL) /* run through list */
  {
    printf("%d ", list->info);
    list = list->next;
  }
  printf("\n");
}

/******************* write_list() *****************/
/** Writes all elements of a list to 'file'      **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**           file:  where to write (e.g. stdout)**/
/** RETURNS:                                     **/
/**          nothing                             **/
/**************************************************/
void write_list(elem_t *list, FILE *file)
{
  while (list != NULL) /* run through list */
  {
    fprintf(file, "%d ", list->info);
    list = list->next;
  }
  fprintf(file, "\n");
}

/****************** search_info() *****************/
/** Search for 'value' in 'list'                 **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**          value: to be found                  **/
/** RETURNS:                                     **/
/**  pointer to element of NULL if not found     **/
/**************************************************/
elem_t *search_info(elem_t *list, int value)
{
  while ((list != NULL) && (list->info != value)) /* run through list */
    list = list->next;
  return (list);
}

/****************** remove_value() ****************/
/** Search for 'value' in 'list' and remove it   **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**          value: to be removed                **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *remove_value(elem_t *list, int value)
{
  elem_t *p, *p_pred;

  p_pred = NULL;
  p = list;

  while ((p != NULL) && (p->info != value)) /* run through list */
  {
    p_pred = p;
    p = p->next;
  }
  if (p == NULL)   /* not found */
    return (list); /* nothing happens */

  if (p == list) /* remove first element ? */
  {
    list = p->next;
  }
  else /* remove element not being first */
  {
    p_pred->next = p->next;
  }
  p->next = NULL; /* remove element from list */
  return (list);
}
