#ifndef STRUCTURES_STRUCTURES_H_
#define STRUCTURES_STRUCTURES_H_

#include <stdlib.h>

typedef enum Lexeme_type { OPERATOR, OPERAND } Lexeme_type;

typedef struct Stack_node {
    char *lexeme;
    Lexeme_type type;
} Stack_node;

typedef struct Stack {
    Stack_node *stack;
    int stack_head;
    int capacity;
} Stack;

Stack *init_stack(int length);
int pop(Stack *my_stack, Stack_node *last_node);
int push(Stack *my_stack, Stack_node new_node);

#endif  // STRUCTURES_STRUCTURES_H_
