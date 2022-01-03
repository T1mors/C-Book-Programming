/*******************************************************************/
/*** Implementation of single-linked lists                       ***/
/*** Main program: includes a bug, such that one part of the     ***/
/*** list is lost. Used as example for debugging.                ***/
/***                                                             ***/
/*** Compile:  cc -o list_error list_error.c list.c              ***/
/***                                                             ***/
/*** Sample program  from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Debugging                                          ***/
/*** Section: gdb                                                ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"



int main(int argc, char *argv[])
{
  elem_t *list, *elem, *elem2, *elem3;
  
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
  elem->next = NULL;
  elem3 = create_element(33);
  list = insert_element(list, elem3, elem2);


  return(0);
}
