#ifndef SRC_MORPHOLOGICAL_ANALYSIS_H_
#define SRC_MORPHOLOGICAL_ANALYSIS_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "s21_stack.h"
#include <stdlib.h>

const char* which_operator(char* op, int is_unary);
double atof_my(char* number);
size_t is_operator(char* str);
size_t is_number(char* str);
int is_unary(char* op);
int is_prefix(char* op);
int is_binary(char* op);
int rank(char* op);
List* parse(char* input_string);

double compute_prefix(double number, char* op);
double compute_binary(double number1, double number2, char* op);

#ifdef __cplusplus
}
#endif

#endif  // SRC_MORPHOLOGICAL_ANALYSIS_H_
