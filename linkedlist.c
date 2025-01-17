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
    free(current->element);
    free(current);
    current = current->next;
  }
  list->first = NULL;
  list->last = NULL;
  list->length = 0;
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

Status add_unique(List_ptr list, Element element, Matcher matcher)
{
  Node_ptr current = list->first;
  while (current != NULL)
  {
    if ((*matcher)(element, current->element))
      return Failure;
    current = current->next;
  }
  return add_to_list(list, element);
}

Status insert_at(List_ptr list, Element element, int position)
{
  if (position == list->length)
    return add_to_list(list, element);
  if (position == 0)
    return add_to_start(list, element);
  if (position < 0 || position > list->length)
    return Failure;
  Node_ptr current = list->first;
  for (int index = 1; index < position; index++)
  {
    current = current->next;
  }
  Node_ptr node = create_node(element);
  node->next = current->next;
  current->next = node;
  list->length++;
  return Success;
}

Element remove_from_end(List_ptr list)
{
  if (list->length == 0)
    return NULL;
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
  if (list->length == 0)
    return NULL;
  Node_ptr head = list->first;
  Element removing_element = head->element;
  list->first = head->next;
  free(head);
  if (list->first == NULL)
    list->last = NULL;
  list->length--;
  return removing_element;
}

Element remove_at(List_ptr list, int position)
{
  if (position < 0 || position >= list->length)
    return NULL;
  if (position == list->length - 1)
    return remove_from_end(list);
  if (position == 0)
    return remove_from_start(list);
  Node_ptr current = list->first;
  for (int index = 1; index < position; index++)
  {
    current = current->next;
  }
  Node_ptr node_to_be_free = current->next;
  current->next = current->next->next;
  list->length--;
  Element removing_element = node_to_be_free->element;
  free(node_to_be_free);
  return removing_element;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher)
{
  int position = 0;
  Node_ptr current = list->first;
  while (current != NULL)
  {
    if ((*matcher)(current->element, element))
      return remove_at(list, position);
    current = current->next;
    position++;
  }
  return (Element) NULL;
}

List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher)
{
  int position = 0;
  List_ptr elemments_list = create_list();
  Node_ptr current = list->first;
  while (current != NULL)
  {
    Node_ptr next = current->next;
    if ((*matcher)(current->element, element))
    {
      Element removed_element = remove_at(list, position);
      add_to_list(elemments_list, removed_element);
    }
    else
    {
      position++;
    }
    current = next;
  }
  return elemments_list;
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

Element reduce(List_ptr src, Element init, Reducer reducer)
{
  int *final_result = malloc(sizeof(int));
  *final_result = *(int *)init;
  Node_ptr current = src->first;
  while (current != NULL)
  {
    Element reducer_result = (*reducer)(final_result, current->element);
    free(final_result);
    final_result = (int *)reducer_result;
    current = current->next;
  }
  return (Element)final_result;
}

List_ptr filter(List_ptr src, Predicate predicate)
{
  List_ptr filter_list = create_list();
  Node_ptr current = src->first;
  while (current != NULL)
  {
    if ((*predicate)(current->element))
    {
      int *element = malloc(sizeof(int));
      *element = *(int *)current->element;
      add_to_list(filter_list, element);
    }
    current = current->next;
  }
  return filter_list;
}

void forEach(List_ptr src, ElementProcessor processor)
{
  Node_ptr current = src->first;
  while (current != NULL)
  {
    (*processor)(current->element);
    current = current->next;
  }
}

List_ptr reverse(List_ptr src)
{
  List_ptr reverse_list = create_list();
  Node_ptr current = src->first;
  while (current != NULL)
  {
    int *element = malloc(sizeof(int));
    *element = *(int *)current->element;
    add_to_start(reverse_list, element);
    current = current->next;
  }
  return reverse_list;
}

Node_ptr find_node(List_ptr list, int index)
{
  Node_ptr current = list->first;
  for (int i = 0; i < index; i++)
  {
    current = current->next;
  }
  return current;
}

void selection_sort(List_ptr list, Comparator comparator)
{
  for (int i = 0; i < list->length; i++)
  {
    int index_of_min = i;
    for (int j = i + 1; j < list->length; j++)
    {
      if (comparator(find_node(list, index_of_min)->element, find_node(list, j)->element))
      {
        index_of_min = j;
      }
    }
    Node_ptr i_node = find_node(list, i);
    Node_ptr min_node = find_node(list, index_of_min);
    Element temp = i_node->element;
    i_node->element = min_node->element;
    min_node->element = temp;
  }
}

void bubble_sort(List_ptr list, Comparator comparator)
{
  int is_swap = 0;
  for (int i = 0; i < list->length; i++)
  {
    for (int j = 0; j < list->length - 1; j++)
    {
      Node_ptr current_node = find_node(list, j);
      if (comparator(current_node->element, current_node->next->element))
      {
        Node_ptr next_node = current_node->next;
        Element temp = next_node->element;
        next_node->element = current_node->element;
        current_node->element = temp;
        is_swap = 1;
      }
    }
    if (!is_swap) return;
    is_swap = 0;
  }
}

void insertion_sort(List_ptr list, Comparator comparator)
{
  for (int i = 0; i < list->length; i++)
  {
    for (int j = i; j > 0; j--)
    {
      Node_ptr prev_node = find_node(list, j - 1);
      if (comparator(prev_node->element, prev_node->next->element))
      {
        Node_ptr j_node = prev_node->next;
        Element temp = j_node->element;
        j_node->element = prev_node->element;
        prev_node->element = temp;
      }
    }
  }
}

void quick_sort(List_ptr list, Comparator comparator, int slice_point, int length)
{
  if (length - slice_point <= 1) return;
  int pivot_pos = length - 1;
  Element pivot = find_node(list, pivot_pos)->element;
  int index = slice_point;
  Pair pair = {NULL, find_node(list, index)};
  while(index < pivot_pos)
  {
    pair.prev = pair.current;
    pair.current = pair.current->next;
    if (comparator(pair.prev->element, pivot))
    {
      Element element = remove_at(list, index);
      insert_at(list, element, length - 1);
      pivot_pos--;
      index--;
    }
    index++;
  }
  quick_sort(list, comparator, slice_point, pivot_pos);
  quick_sort(list, comparator, pivot_pos + 1, length);
}