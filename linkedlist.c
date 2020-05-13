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

Status add_to_list(List_ptr list, Element element)
{
  Node_ptr node = create_node(element);
  if (list->first == NULL)
  {
    list->first = node;
  }
  else
  {
    list->last->next = node;
  }
  list->last = node;
  list->length++;
  return Success;
}

Status add_to_start(List_ptr list, Element element)
{
  if (list->first == NULL)
    return add_to_list(list, element);
  Node_ptr node = create_node(element);
  node->next = list->first;
  list->first = node;
  list->length++;
  return Success;
}

Element remove_from_end(List_ptr list)
{
  Pair pair = {NULL, list->first};
  for (int index = 1; index < list->length; index++)
  {
    pair.prev = pair.current;
    pair.current = pair.current->next;
  }
  list->last = pair.prev;
  if (list->last == NULL)
    list->first = list->last;
  if (list->last != NULL)
    list->last->next = NULL;
  Element removing_element = pair.current->element;
  free(pair.current);
  list->length--;
  return removing_element;
}

Element remove_from_start(List_ptr list)
{
  Node_ptr head = list->first;
  Element removing_element = head->element;
  list->first = head->next;
  free(head);
  if (list->first == NULL)
    list->last = NULL;
  list->length--;
  return removing_element;
}

/////////////////////////////////////////////////

List_ptr map(List_ptr src, Mapper mapper)
{
  List_ptr map_list = create_list();
  Node_ptr current = src->first;
  while (current != NULL)
  {
    add_to_list(map_list, (*mapper)(current->element));
    current = current->next;
  }
  return map_list;
}