#ifndef SRC_MORPHOLOGICAL_ANALYSIS_H_
#define SRC_MORPHOLOGICAL_ANALYSIS_H_
#include "s21_stack.h"
#include <stdlib.h>

const char* which_operator(char* operator, int is_unary);
double atof_my(char* number);
size_t is_operator(char* str);
size_t is_number(char* str);
stack_node* parse(char* input_string);

#endif  // SRC_MORPHOLOGICAL_ANALYSIS_H_