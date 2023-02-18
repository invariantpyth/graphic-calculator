#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

typedef struct stack_struct {
  char* lexeme;
  struct stack_struct* previous_node;
} stack_node;

stack_node* push(char* lexeme, stack_node* previous_node);
char* pop(stack_node** stack_top);

#endif  // SRC_S21_STACK_H_