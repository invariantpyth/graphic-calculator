#include "s21_sort_station.h"

#include <stdio.h>
#include <stdlib.h>

#include "s21_morphological_analysis.h"

void free_all_numbers(List* lst) {
  Node* start_node = lst->start;
  while (start_node != NULL) {
    Node* next_node = start_node->another_node;
    if (is_number(start_node->lexeme)) {
      free(start_node->lexeme);
    }
    start_node = next_node;
  }
}

static int is_ok_for_binaries(char* lex, Stack* temp_stack) {
  return is_prefix(lex) ||
         (temp_stack->current_top != NULL &&
          *temp_stack->current_top->lexeme != '(' &&
          ((rank(lex) < rank(temp_stack->current_top->lexeme)) ||
           (*temp_stack->current_top->lexeme != '^' &&
            (rank(lex) == rank(temp_stack->current_top->lexeme)))));
}

List* turn_to_rev_pol(char* input_string) {
  List* expression = parse(input_string);
  int error = 0;
  if (expression == NULL) {
      return NULL;
  }
  Stack* temp_stack = calloc(1, sizeof(Stack));
  List* rpn = calloc(1, sizeof(List));
  Node* current_lex_from_input = expression->start;
  while (current_lex_from_input != NULL && error == 0) {
    char* lex = current_lex_from_input->lexeme;
    current_lex_from_input = current_lex_from_input->another_node;
    if (is_number(lex) || *lex == 'x') {
      push_back(lex, rpn);
    } else if (is_prefix(lex)) {
      push(lex, temp_stack);
    } else if (*lex == '(') {
      push(lex, temp_stack);
    } else if (*lex == ')') {
      while (*temp_stack->current_top->lexeme != '(' && error == 0) {
        push_back(pop(temp_stack), rpn);
        error = (temp_stack == NULL) ? 1 : 0;
      }
      pop(temp_stack);
    } else if (is_binary(lex)) {
      while (is_ok_for_binaries(lex, temp_stack)) {
        push_back(pop(temp_stack), rpn);
      }
      push(lex, temp_stack);
    }
  }
  while (temp_stack->current_top != NULL) {
    char* op = pop(temp_stack);
    if (is_number(op)) {
      error = 1;
    }
    push_back(op, rpn);
  }
  if (error != 0) {
    free_all_numbers(rpn);
    destroy_list(rpn);
    rpn = NULL;
  }
  free(temp_stack);
  destroy_list(expression);

  return rpn;
}

static int has_one_in_stack(Stack* st) { return (st->current_top != NULL); }

static int has_two_in_stack(Stack* st) {
  return (st->current_top != NULL && st->current_top->another_node != NULL);
}

double evaluate(char* expression) {
  List* rpn = turn_to_rev_pol(expression);
  int err = 0;
  double nan = 0.0 / 0.0;
  if (rpn == NULL) {
      return nan;
  }
  Stack* numbers = calloc(1, sizeof(Stack));
  Node* current_node = rpn->start;
  while (current_node != NULL && !err) {
    if (is_number(current_node->lexeme)) {
      double* number = calloc(1, sizeof(double));
      *number = atof_my(current_node->lexeme);
      push((char*)number, numbers);
    } else if (is_prefix(current_node->lexeme) && has_one_in_stack(numbers)) {
      double* number = (double*)numbers->current_top->lexeme;
      *number = compute_prefix(*number, current_node->lexeme);
    } else if (is_binary(current_node->lexeme) && has_two_in_stack(numbers)) {
      double* number1 = (double*)pop(numbers);
      double* number2 = (double*)numbers->current_top->lexeme;
      *number2 = compute_binary(*number2, *number1, current_node->lexeme);
      free(number1);
    } else {
        err = 1;
    }
    current_node = current_node->another_node;
  }
  double* number = NULL;
  double ret_value = nan;
  if (numbers->current_top != NULL) {
      number = (double*)pop(numbers);
      ret_value = *number;
  }
  free(number);
  free_all_numbers(rpn);
  destroy_list(rpn);
  free(numbers);
  return ret_value;
}
