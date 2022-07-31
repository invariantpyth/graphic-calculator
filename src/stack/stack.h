#ifndef STACK_STACK_H_
#define STACK_STACK_H_

#include <stdlib.h>

typedef enum Lexeme_type { OPERATOR, OPERAND } Lexeme_type;

typedef struct Stack_node {
  char *lexeme;
  Lexeme_type type;
} Stack_node;

typedef struct Stack {
  Stack_node *stack;
  Stack_node *stack_head;
} Stack;

Stack *init_stack(int length);
Stack_node *pop(Stack *my_stack);
void push(Stack *my_stack);

#endif // STACK_STACK_H_
