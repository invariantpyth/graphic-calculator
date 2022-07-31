#ifndef TRANSFORMATIONS_POSTFIX_H_
#define TRANSFORMATIONS_POSTFIX_H_

#include "../structures/structures.h"

// "+", "-", "*", "/", "^", "sin", "cos", "tan", "ctg", "ln", "(", ")".

int parse(char* expression_string, Expression* infix_expression);
int transform(Expression* my_expression);



#endif  // TRANSFORMATIONS_POSTFIX_H_
