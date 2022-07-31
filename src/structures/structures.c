#include "structures.h"

#include <stdlib.h>

Stack *init_stack(int length) {
    Stack *new_stack = malloc(sizeof(Stack_node) * length);
    new_stack->capacity = length;
    new_stack->stack_head = 0;
    return new_stack;
}

int pop(Stack *my_stack, Stack_node *last_node) {
    int flag = 1;
    if (my_stack->stack_head != -1) {
        *last_node = my_stack->stack[my_stack->stack_head];
        my_stack->stack_head = my_stack->stack_head - 1;
    } else {
        flag = 0;
    }
    return flag;
}

int push(Stack *my_stack, Stack_node new_node) {
    int flag = 1;
    if (my_stack->stack_head + 1 < my_stack->capacity) {
        my_stack->stack_head = my_stack->stack_head + 1;
        my_stack->stack[my_stack->stack_head] = new_node;
    } else {
        flag = 0;
    }
    return flag;
}
