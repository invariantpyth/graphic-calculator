#include "s21_morphological_analysis.h"

#include <string.h>

char* which_operator(char* operator, int is_unary) {
  size_t length = is_operator(operator);
  char buffer[5] = {0};
  strncpy(buffer, operator, length);
  size_t i = 0;
  while (!strcmp(buffer, operators[i])) {
    i++;
  }
}
size_t is_operator(char* str) {
  size_t ret_value = 0;
  if (!is_number(str)) {
    while (str[ret_value] != ' ' && str[ret_value] != '(' &&
           !is_number(str + ret_value) && str[ret_value] != 0) {
            ret_value++;
    }
    ret_value;
  }
  return ret_value;
}
size_t is_number(char* str) { return strspn(str, "1234567890.Ee"); }
char** parse(char* input_string) {}

double atof(char* number) {
  double ret_value = 0;
  sscanf(number, "%lf", &ret_value);
  return ret_value;
}