#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct Node{
  char* lexeme;
  struct Node* another_node;
} Node;

typedef struct {
  Node *current_top;
} Stack;

typedef struct {
  Node *start;
  Node *end;
} List;

void push(char* lexeme, Stack* st);
char* pop(Stack* st);
void print_stack(Stack st);

void push_back(char* lexeme, List* lst);
void print_list(List lst);
void destroy_list(List *lst);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_STACK_H_
