#ifndef STRUCTURES_STRUCTURES_H_
#define STRUCTURES_STRUCTURES_H_

#include <stdlib.h>

typedef enum Lexeme_type { OPERATOR, OPERAND } Lexeme_type;

typedef struct Lexeme {
    char *lexeme;
    Lexeme_type type;
} Lexeme;

typedef struct Stack {
    Lexeme *stack;
    int stack_head;
    int capacity;
} Stack;

Stack *init_stack(int length);
int pop(Stack *my_stack, Lexeme *last_node);
int push(Stack *my_stack, Lexeme new_node);

#endif  // STRUCTURES_STRUCTURES_H_
