/*******************************************************************/
/*** Implementation of single-linked lists                       ***/
/*** Main program                                                ***/
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



int main(int argc, char *argv[])
{
  elem_t *list, *elem, *elem2;
  
  list = NULL;
  elem = create_element(5);
  list = insert_element(list, elem, NULL);
  elem2 = create_element(3);
  list = insert_element(list, elem2, NULL);
  elem2 = create_element(6);
  list = insert_element(list, elem2, elem);
  elem2 = create_element(10);
  list = insert_element(list, elem2, elem);
  elem2 = create_element(7);
  list = insert_element(list, elem2, elem);
  print_list(list);

  /*list = mergesort_list(list);
  printf("sort list\n");
  print_list(list);*/

  /*printf("delete 6:\n");
  elem = search_info(list, 6);
  list = remove_element(list, elem);
  delete_element(elem);
  print_list(list);

  printf("delete first element\n");
  elem = list;
  list = remove_element(list, elem);
  delete_element(elem);
  print_list(list);*/

  return(0);
}
