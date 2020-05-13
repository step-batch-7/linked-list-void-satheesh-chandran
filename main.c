#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

Element get_input_number(void)
{
  int *number = malloc(sizeof(int));
  printf("Enter number : ");
  scanf("%d\n", number);
  return number;
}

void display_linked_number_list(List_ptr list)
{
  Node_ptr current = list->first;
  while (current != NULL)
  {
    printf("%d ", *(int *)current->element);
    current = current->next;
  }
  printf("\n");
}

void free_list(List_ptr list)
{
  Node_ptr current = list->first;
  while (current != NULL)
  {
    Node_ptr node_to_be_free = current;
    current = current->next;
    free(node_to_be_free->element);
    free(node_to_be_free);
  }
  free(list);
}

int main()
{
  List_ptr list = create_list();

  Element input_number = get_input_number();
  while (*(int *)input_number != 99)
  {
    add_to_list(list, input_number);
    input_number = get_input_number();
  }
  display_linked_number_list(list);
  free_list(list);
  return 0;
}
