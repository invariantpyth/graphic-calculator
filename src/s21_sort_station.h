#ifndef SRC_S21_SORT_STATION_H_
#define SRC_S21_SORT_STATION_H_

#include "s21_stack.h"

typedef struct output_string {
  char** lexs;
  int amount;
} output_string;

void push_back(output_string *output, char* lex);
output_string* turn_to_rev_pol(stack_node* expression);

#endif  // SRC_S21_SORT_STATION_H_