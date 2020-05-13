#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// typedef struct Prev_Current_pair
// {
//   Node_ptr prev;
//   Node_ptr current;
// } Pair;

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

Status clear_list(List_ptr list)
{
  Node_ptr current = list->first;
  while (current != NULL)
  {
    Node_ptr node_to_be_free = current;
    current = current->next;
    free(node_to_be_free->element);
    free(node_to_be_free);
  }
  return Success;
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

Status add_to_start(List_ptr src, Element element)
{
  if (src->first == NULL)
    return add_to_list(src, element);
  Node_ptr node = create_node(element);
  node->next = src->first;
  src->first = node;
  src->length++;
  return Success;
}

// Element remove_from_end(List_ptr list)
// {
//   Pair pair = {NULL, list->first};
//   for (int index = 0; index < list->length; index++)
//   {
//     pair.prev = pair.current;
//     pair.current = pair.current->next;
//   }
// }