#include "s21_stack.h"

#include <stdlib.h>

stack_node* push(char* lexeme, stack_node* previous_node) {
  stack_node* new_node = malloc(sizeof(stack_node));
  new_node->lexeme = lexeme;
  new_node->previous_node = previous_node;
  return new_node;
}

char* pop(stack_node* stack_top) {
  char* ret_str = stack_top->lexeme;
  stack_node* new_top = stack_top->previous_node;
  free(stack_top);
  stack_top = new_top;
  return ret_str;
}