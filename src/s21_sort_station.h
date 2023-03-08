#ifndef SRC_S21_SORT_STATION_H_
#define SRC_S21_SORT_STATION_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "s21_stack.h"

List* turn_to_rev_pol(char* input_string);
void free_all_numbers(List* lst);
double evaluate(char* expression, double x);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_SORT_STATION_H_
