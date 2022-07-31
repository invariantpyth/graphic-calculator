#ifndef STACK_STACK_H_
#define STACK_STACK_H_

#include <stdlib.h>

typedef enum {
    OPERATOR,
    OPERAND
} Lexeme_type;

typedef struct {
    char* lexeme;
    Lexeme_type type;
} Stack_node;

typedef struct {
    Stack_node* stack;
    Stack_node* stack_head;
} Stack;

#endif // STACK_STACK_H_