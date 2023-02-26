#include "s21_sort_station.h"

#include <stdio.h>
#include <stdlib.h>

#include "s21_morphological_analysis.h"

// void push_back(output_string* output, char* lex) {
//   output->lexs = realloc(output->lexs, output->amount + 1);
//   output->lexs[output->amount] = lex;
//   output->amount++;
// }

// static void print_stack(stack_node* st) {
//   printf("stack: ");
//   while (st != NULL) {
//     printf("%s ", st->lexeme);
//     st = st->previous_node;
//   }
//   printf("\n");
// }

// static void print_string(output_string* st) {
//   printf("output: ");
//   for (int i = 0; i < st->amount; i++) {
//     printf("%s ", st->lexs[i]);
//   }
//   printf("\n\n");
// }

// static void destruct_stack(stack_node* stack_top) {
//   while (stack_top != NULL) {
//     char* cont = pop(&stack_top);
//     if (is_number(cont)) {
//       free(cont);
//     }
//   }
// }

void free_all_numbers(List* lst) {
  Node* start_node = lst->start;
  while (start_node->another_node != NULL) {
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
          ((rank(lex) <= rank(temp_stack->current_top->lexeme)) ||
           (*temp_stack->current_top->lexeme != '^' &&
            (rank(lex) == rank(temp_stack->current_top->lexeme)))));
}

List* turn_to_rev_pol(char* input_string) {
  List* expression = parse(input_string);
  int error = 0;
  Stack* temp_stack = calloc(1, sizeof(Stack));
  List* rpn = calloc(1, sizeof(List));
  Node* current_lex_from_input = expression->start;
  while (current_lex_from_input != NULL && error == 0) {
    char* lex = current_lex_from_input->lexeme;
    current_lex_from_input = current_lex_from_input->another_node;
    if (is_number(lex)) {
      push_back(lex, rpn);
      print_list(*rpn);
      print_stack(*temp_stack);
      printf("\n");
    } else if (is_prefix(lex)) {
      push(lex, temp_stack);
      print_list(*rpn);
      print_stack(*temp_stack);
      printf("\n");
    } else if (*lex == '(') {
      push(lex, temp_stack);
      print_list(*rpn);
      print_stack(*temp_stack);
      printf("\n");
    } else if (*lex == ')') {
      while (*temp_stack->current_top->lexeme != '(' && error == 0) {
        push_back(pop(temp_stack), rpn);
        error = (temp_stack == NULL) ? 1 : 0;
        print_list(*rpn);
        print_stack(*temp_stack);
        printf("\n");
      }
      pop(temp_stack);
      print_list(*rpn);
      print_stack(*temp_stack);
      printf("\n");
    } else if (is_binary(lex)) {
      while (is_ok_for_binaries(lex, temp_stack)) {
        push_back(pop(temp_stack), rpn);
        print_list(*rpn);
        print_stack(*temp_stack);
        printf("\n");
      }
      push(lex, temp_stack);
      print_list(*rpn);
      print_stack(*temp_stack);
      printf("\n");
    }
  }
  while (temp_stack->current_top != NULL && error == 0) {
    char* op = pop(temp_stack);
    if (is_number(op)) {
      error = 1;
    } else {
      push_back(op, rpn);
    }
  }
  free(temp_stack);
  destroy_list(expression);
  free(expression);
  // if (error != 0) {
  //   destruct_stack(expression);
  //   destruct_stack(temp_stack);
  //   destruct_output_string(reverse_polish_expression);
  // }
  return rpn;
}
