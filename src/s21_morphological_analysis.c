#include "s21_morphological_analysis.h"

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
const char unary_plus[] = "+";
const char unary_minus[] = "-";
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
                           unary_minus,
                           unary_plus};
const char variable[] = "x";

const char* which_operator(char* operator, int is_unary) {
  size_t length = is_operator(operator);
  char buffer[5] = {0};
  strncpy(buffer, operator, length);
  size_t i = 0;
  while (strcmp(buffer, operators[i])) {
    i++;
  }
  if (i == 13 && is_unary) {
    i = 17;
  }
  if (i == 14 && is_unary) {
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

stack_node* parse(char* input_string) {
  stack_node* lexemes = NULL;
  size_t point = 0;
  while (input_string[point] != '\0') {
    size_t block_size = 0;
    if ((block_size = is_operator(input_string + point))) {
      int is_unary = 0;
      if (lexemes == NULL || lexemes->lexeme == open_parenthesis) {
        is_unary = 1;
      }
      const char* op = which_operator(input_string + point, is_unary);
      if (lexemes != NULL &&
          (not_in_operators(lexemes->lexeme) ||
           lexemes->lexeme == close_parenthesis) &&
          !is_symbol_operator(*op)) {
        lexemes = push((char*)multiply, lexemes);
      }
      lexemes = push((char*)op, lexemes);
      point += block_size;
    }
    if ((block_size = is_number(input_string + point))) {
      char* number = calloc(block_size + 1, sizeof(char));
      strncpy(number, input_string + point, block_size);
      lexemes = push(number, lexemes);
      point += block_size;
    }
    if (input_string[point] == '(') {
      lexemes = push((char*)open_parenthesis, lexemes);
      point++;
    }
    if (input_string[point] == ')') {
      lexemes = push((char*)close_parenthesis, lexemes);
      point++;
    }
    if (input_string[point] == 'x') {
      if (lexemes != NULL && (not_in_operators(lexemes->lexeme) ||
                              lexemes->lexeme == close_parenthesis)) {
        lexemes = push((char*)multiply, lexemes);
      }
      lexemes = push((char*)variable, lexemes);
      point++;
    }
    if (input_string[point] == ' ') {
      point++;
    }
  }
  stack_node* reversed_lexemes = NULL;
  do {
    char* str = pop(&lexemes);
    reversed_lexemes = push(str, reversed_lexemes);
  } while (lexemes != NULL);
  return reversed_lexemes;
}

double atof_my(char* number) {
  double ret_value = 0;
  sscanf(number, "%lf", &ret_value);
  return ret_value;
}
