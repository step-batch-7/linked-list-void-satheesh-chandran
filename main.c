#include <stdio.h>
#include <stdlib.h>
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

void increment(Element element)
{
  int *number = (int *)element;
  (*number)++;
}

Status is_numbers_equal(Element data1, Element data2)
{
  return *(int *)data1 == *(int *)data2 ? Success : Failure;
}

/////////////////////////////////////////////////

Element get_input_number(const char question[])
{
  int *number_ptr = malloc(sizeof(int));
  printf("%s", question);
  scanf("%d\n",  number_ptr);
  return (Element)number_ptr;
}

void display_element(Element element)
{
  if (element == NULL)
  {
    printf("\n");
    return;
  }
  printf("%d\n", *(int *)element);
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

void print_status(Status status)
{
  if (status == Success)
  {
    printf("Done");
    return;
  }
  printf("Not Done");
}

void destroy_list(List_ptr list)
{
  clear_list(list);
  free(list);
}

void perform_map(List_ptr list)
{
  List_ptr squares_of_numbers = map(list, &square);
  printf("\nSQUARE OF NUMBERS\n");
  display_linked_number_list(squares_of_numbers);
  destroy_list(squares_of_numbers);
}

void perform_filter(List_ptr list)
{
  List_ptr even_numbers = filter(list, &is_even);
  printf("\nEVEN NUMBERS\n");
  display_linked_number_list(even_numbers);
  destroy_list(even_numbers);
}

void perform_reduce(List_ptr list)
{
 int initial = 0;
  Element sum_of_all_numbers = reduce(list, &initial, &add);
  printf("\nSUM OF ALL NUMBERS\n");
  display_element(sum_of_all_numbers);
  free(sum_of_all_numbers);
}

void perform_reverse(List_ptr list)
{
  List_ptr reverse_list = reverse(list);
  printf("\nREVERSE OF LIST\n");
  display_linked_number_list(reverse_list);
  destroy_list(reverse_list);
}

void perform_forEach(List_ptr list)
{
  forEach(list, &increment);
  printf("\nINCREMENTED BY ONE\n");
  display_linked_number_list(list);
}

int main()
{
  List_ptr list = create_list();

  Element input_number = get_input_number("Enter number : ");
  while (*(int *)input_number != 99)
  {
    add_to_list(list, input_number);
    input_number = get_input_number("Enter number : ");
  }

  printf("\nYOU ENTERED\n");
  display_linked_number_list(list);

  perform_map(list);
  perform_filter(list);
  perform_reduce(list);
  perform_reverse(list);
  perform_forEach(list);

  // input_number = get_input_number("Enter number : ");
  // input_number = get_input_number("Enter number : ");
  // add_to_start(list, input_number);

  // int *number = malloc(sizeof(int));
  // *number = 10;
  // insert_at(list, number, 2);
  // display_linked_number_list(list);

  // Element removed_element = remove_from_start(list);
  // printf("%d\n", *(int *)removed_element);
  // free(removed_element);
  // display_linked_number_list(list);

  // Element removed_element = remove_at(list, 2);
  // display_linked_number_list(list);

  // int *number = malloc(sizeof(int));
  // *number = 1;
  // Element removed_element = remove_first_occurrence(list, number, &is_numbers_equal);
  // List_ptr removed_elements = remove_all_occurrences(list, number, &is_numbers_equal);
  // display_linked_number_list(list);
  // display_linked_number_list(removed_elements);

  // int *number = malloc(sizeof(int));
  // *number = 10;
  // add_unique(list, number, &is_numbers_equal);
  // display_linked_number_list(list);

  destroy_list(list);
  return 0;
}
