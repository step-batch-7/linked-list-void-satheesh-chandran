#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/////////////////////////////////////////////////

Element square(Element element)
{
  int *result = malloc(sizeof(int));
  int number = *(int *)element;
  *result = number * number;
  return (Element)result;
}

Element add(Element data1, Element data2)
{
  int *result = malloc(sizeof(int));
  *result = *(int *)data1 + *(int *)data2;
  return (Element)result;
}

Status is_even(Element element)
{
  return *(int *)element % 2 == 0 ? Success : Failure;
}

/////////////////////////////////////////////////

Element get_input_number(void)
{
  int *number = malloc(sizeof(int));
  printf("Enter number : ");
  scanf("%d\n",  number);
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
  clear_list(list);
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

  // input_number = get_input_number();
  // input_number = get_input_number();
  // add_to_start(list, input_number);

  // Element removed_element = remove_from_start(list);
  // printf("%d\n", *(int *)removed_element);
  // free(removed_element);
  // display_linked_number_list(list);

  // List_ptr squares_of_numbers = map(list, &square);
  // display_linked_number_list(squares_of_numbers);
  // free_list(squares_of_numbers);

  // int initial = 0;
  // Element sum_of_all_numbers = reduce(list, &initial, &add);
  // printf("%d\n", *(int *)sum_of_all_numbers);
  // free(sum_of_all_numbers);

  List_ptr even_numbers = filter(list, &is_even);
  display_linked_number_list(even_numbers);
  free_list(even_numbers);

  free_list(list);
  return 0;
}
