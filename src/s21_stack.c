#include "s21_stack.h"

#include <stdio.h>
#include <stdlib.h>

void push(char* lexeme, Stack* st) {
  Node* new_top = calloc(1, sizeof(Node));
  new_top->lexeme = lexeme;
  new_top->another_node = st->current_top;
  st->current_top = new_top;
}

char* pop(Stack* st) {
  char* ret_str = st->current_top->lexeme;
  Node* node_to_free = st->current_top;
  st->current_top = node_to_free->another_node;
  free(node_to_free);
  return ret_str;
}

void print_stack(Stack st) {
  printf("stack: ");
  Node* node_to_print = st.current_top;
  while (node_to_print != NULL) {
    printf("%s ", node_to_print->lexeme);
    node_to_print = node_to_print->another_node;
  }
  printf("\n");
}

void push_back(char* lexeme, List* lst) {
  Node* new_node = calloc(1, sizeof(Node));
  new_node->lexeme = lexeme;
  if (lst->start == NULL) {
    lst->start = new_node;
    lst->end = new_node;
  } else {
    lst->end->another_node = new_node;
    lst->end = new_node;
  }
}

void destroy_list(List *lst) {
  Node* start_node = lst->start;
  while (start_node->another_node != NULL) {
    Node* next_node = start_node->another_node;
    free(start_node);
    start_node = next_node;
  }
}

void print_list(List lst) {
  printf("List: ");
  Node* start_node = lst.start;
  while (start_node != NULL) {
    printf("%s ", start_node->lexeme);
    start_node = start_node->another_node;
  }
  printf("\n");
}
