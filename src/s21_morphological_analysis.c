#include "s21_morphological_analysis.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_stack.h"

#define OPERATORS_COUNT 19
const char sin_o[] = "sin";
const char cos_o[] = "cos";
const char tan_o[] = "tan";
const char acos_o[] = "acos";
const char asin_o[] = "asin";
const char atan_o[] = "atan";
const char sqrt_o[] = "sqrt";
const char ln_o[] = "ln";
const char log_o[] = "log";
const char mod_o[] = "mod";
const char open_parenthesis[] = "(";
const char close_parenthesis[] = ")";
const char plus[] = "+";
const char minus[] = "-";
const char multiply[] = "*";
const char divide[] = "/";
const char power[] = "^";
const char unary_plus[] = "$";
const char unary_minus[] = "~";
const char* operators[] = {sin_o,
                           cos_o,
                           tan_o,
                           acos_o,
                           asin_o,
                           atan_o,
                           sqrt_o,
                           ln_o,
                           log_o,
                           close_parenthesis,
                           open_parenthesis,
                           mod_o,
                           plus,
                           minus,
                           multiply,
                           divide,
                           power,
                           unary_plus,
                           unary_minus};
const char variable[] = "x";

const char* which_operator(char* op, int is_unary) {
  size_t length = is_operator(op);
  char buffer[5] = {0};
  strncpy(buffer, op, length);
  size_t i = 0;
  while (strcmp(buffer, operators[i])) {
    i++;
  }
  if (i == 12 && is_unary) {
    i = 17;
  }
  if (i == 13 && is_unary) {
    i = 18;
  }
  return operators[i];
}

int is_symbol_operator(char sym) { return !!strchr("+-()^*/", sym); }

size_t is_operator(char* str) {
  size_t ret_value = 0;
  if (!is_number(str)) {
    if (is_symbol_operator(str[0])) {
      ret_value = 1;
    } else {
      while (str[ret_value] != ' ' && str[ret_value] != '(' &&
             str[ret_value] != ')' && str[ret_value] != 'x' &&
             !is_number(str + ret_value) && str[ret_value] != 0) {
        ret_value++;
      }
    }
  }
  return ret_value;
}
size_t is_number(char* str) { return strspn(str, "1234567890.Ee"); }

static int not_in_operators(char* pointer) {
  int not_here = 1;
  size_t i = 0;
  while (not_here && i < OPERATORS_COUNT) {
    if (pointer == operators[i]) {
      not_here = 0;
    }
    i++;
  }
  return not_here;
}

List* parse(char* input_string) {
  List* lexemes = calloc(1, sizeof(List));
  size_t point = 0;
  while (input_string[point] != '\0') {
    size_t block_size = 0;
    if ((block_size = is_operator(input_string + point))) {
      int is_unary = 0;
      if (lexemes->end == NULL || lexemes->end->lexeme == open_parenthesis) {
        is_unary = 1;
      }
      const char* op = which_operator(input_string + point, is_unary);
      if (lexemes->end != NULL &&
          (not_in_operators(lexemes->end->lexeme) ||
           lexemes->end->lexeme == close_parenthesis) &&
          !is_symbol_operator(*op)) {
        push_back((char*)multiply, lexemes);
      }
      push_back((char*)op, lexemes);
      point += block_size;
    }
    if ((block_size = is_number(input_string + point))) {
      char* number = calloc(block_size + 1, sizeof(char));
      strncpy(number, input_string + point, block_size);
      push_back(number, lexemes);
      point += block_size;
    }
    if (input_string[point] == '(') {
      if (lexemes->end != NULL && (not_in_operators(lexemes->end->lexeme) ||
                                   lexemes->end->lexeme == close_parenthesis)) {
        push_back((char*)multiply, lexemes);
      }
      push_back((char*)open_parenthesis, lexemes);
      point++;
    }
    if (input_string[point] == ')') {
      push_back((char*)close_parenthesis, lexemes);
      point++;
    }
    if (input_string[point] == 'x') {
      if (lexemes->end != NULL && (not_in_operators(lexemes->end->lexeme) ||
                                   lexemes->end->lexeme == close_parenthesis)) {
        push_back((char*)multiply, lexemes);
      }
      push_back((char*)variable, lexemes);
      point++;
    }
    if (input_string[point] == ' ') {
      point++;
    }
  }
  return lexemes;
}

double atof_my(char* number) {
  double ret_value = 0;
  sscanf(number, "%lf", &ret_value);
  return ret_value;
}

int is_unary(char* op) {
  return (op == unary_minus || op == unary_plus) ? 1 : 0;
}

int is_binary(char* op) { return !(is_unary(op) || is_prefix(op)); }

int is_prefix(char* op) {
  size_t i = 0;
  int ret = 0;
  while (ret == 0 && i < 9) {
    ret = (op == operators[i]) ? 1 : 0;
    i++;
  }
  ret = ret || (op == unary_minus) ? 1 : 0;
  ret = ret || (op == unary_plus) ? 1 : 0;

  return ret;
}

int rank(char* op) {
  int rank_value = 0;
  if (is_prefix(op)) {
    rank_value = 4;
  } else if (op == power) {
    rank_value = 3;
  } else if (op == divide || op == multiply) {
    rank_value = 2;
  } else {
    rank_value = 1;
  }
  return rank_value;
}

double compute_prefix(double number, char* op) {
  double ret_value = 0;
  if (op == sin_o) {
    ret_value = sin(number);
  } else if (op == cos_o) {
    ret_value = cos(number);
  } else if (op == tan_o) {
    ret_value = tan(number);
  } else if (op == acos_o) {
    ret_value = acos(number);
  } else if (op == asin_o) {
    ret_value = asin(number);
  } else if (op == atan_o) {
    ret_value = atan(number);
  } else if (op == sqrt_o) {
    ret_value = sqrt(number);
  } else if (op == ln_o) {
    ret_value = log(number);
  } else if (op == log_o) {
    ret_value = log10(number);
  } else if (op == unary_minus) {
    ret_value = -number;
  } else if (op == unary_plus) {
    ret_value = number;
  }
  return ret_value;
}

double compute_binary(double number1, double number2, char* op) {
  double ret_value = 0;
  if (op == mod_o) {
    ret_value = fmod(number1, number2);
  } else if (op == plus) {
    ret_value = number1 + number2;
  } else if (op == minus) {
    ret_value = number1 - number2;
  } else if (op == multiply) {
    ret_value = number1 * number2;
  } else if (op == divide) {
    ret_value = number1 / number2;
  } else if (op == power) {
    ret_value = pow(number1, number2);
  }
  return ret_value;
}
