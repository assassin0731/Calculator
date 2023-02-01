#ifndef SRC_LIB_DYNAMIC_MODULE_H_
#define SRC_LIB_DYNAMIC_MODULE_H_

struct Stack {
  char **str;
  int *prior;
  double *chislo;
  int size;
  int top;
};

void init(struct Stack *s);
void push_str(struct Stack *s, char *data, int prior);
void push_double(struct Stack *s, double data);
char *pop_str(struct Stack *s);
double pop_double(struct Stack *s);
void destroy(struct Stack *s);
void add_pop(char **exit_str, char *stroka, int *j);

#endif  // SRC_LIB_DYNAMIC_MODULE_H_
