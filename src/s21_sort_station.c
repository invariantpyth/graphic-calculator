#include "s21_sort_station.h"

#include <stdlib.h>

#include "s21_morphological_analysis.h"

void push_back(output_string* output, char* lex) {
  output->lexs = realloc(output->lexs, output->amount + 1);
  output->lexs[output->amount] = lex;
  output->amount++;
}

static void destruct_stack(stack_node* stack_top) {
  while (stack_top != NULL) {
    char* cont = pop(&stack_top);
    if (is_number(cont)) {
      free(cont);
    }
  }
}

static void destruct_output_string(output_string* str) {
  for (int i = 0; i < str->amount; i++) {
    if (is_number(str->lexs[i])) {
      free(str->lexs[i]);
    }
  }
  free(str);
  str = NULL;
}

static int is_ok_for_binaries(char* lex, stack_node* temp_stack) {
  return is_prefix(lex) ||
         (temp_stack != NULL && ((rank(lex) <= rank(temp_stack->lexeme)) ||
                                 (*temp_stack->lexeme != '^' &&
                                  (rank(lex) == rank(temp_stack->lexeme)))));
}

output_string* turn_to_rev_pol(stack_node* expression) {
  int error = 0;
  stack_node* temp_stack = NULL;
  output_string* reverse_polish_expression = calloc(sizeof(output_string), 1);
  while (expression != NULL && error == 0) {
    char* lex = pop(&expression);
    if (is_number(lex) && error == 0) {
      push_back(reverse_polish_expression, lex);
    } else if (is_prefix(lex) && error == 0) {
      push(lex, temp_stack);
    } else if (*lex == '(' && error == 0) {
      push(lex, temp_stack);
    } else if (*lex == ')' && error == 0) {
      char* op = lex;
      while (*op != '(' && error == 0) {
        op = pop(&temp_stack);
        push_back(reverse_polish_expression, op);
        error = (temp_stack == NULL) ? 1 : 0;
      }
    } else if (is_binary(lex) && error == 0) {
      while (is_ok_for_binaries(lex, temp_stack)) {
        push_back(reverse_polish_expression, pop(&temp_stack));
      }
      push(lex, temp_stack);
    }
  }
  while (temp_stack != NULL && error == 0) {
    char* op = pop(&temp_stack);
    if (is_number(op)) {
      error = 1;
    } else {
      push_back(reverse_polish_expression, op);
    }
  }
  if (error != 0) {
    destruct_stack(expression);
    destruct_stack(temp_stack);
    destruct_output_string(reverse_polish_expression);
  }
  return reverse_polish_expression;
}
