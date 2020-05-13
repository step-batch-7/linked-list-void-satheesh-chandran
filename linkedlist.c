#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

Node_ptr create_node(Element element)
{
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = element;
  new_node->next = NULL;
  return new_node;
}

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
  return list;
}

Status add_to_list(List_ptr src, Element element)
{
  Node_ptr node = create_node(element);
  if (src->first == NULL)
  {
    src->first = node;
  }
  else
  {
    src->last->next = node;
  }
  src->last = node;
  src->length++;
  return Success;
}