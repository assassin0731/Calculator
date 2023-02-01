#include "calc.h"

void init(struct Stack *s) {
  s->top = 0;
  s->size = 5;
  s->str = malloc(s->size * sizeof(char *));
  s->chislo = malloc(s->size * sizeof(double));
  s->prior = malloc(s->size * sizeof(int));
}

void push_str(struct Stack *s, char *data, int prior) {
  if (s->top == s->size) {
    s->size += 5;
    s->prior = realloc(s->prior, s->size * sizeof(int));
    s->str = realloc(s->str, s->size * sizeof(char *));
  }
  s->str[s->top] = data;
  s->prior[s->top] = prior;
  s->top++;
}

void push_double(struct Stack *s, double data) {
  if (s->top == s->size) {
    s->size += 5;
    s->chislo = realloc(s->chislo, s->size * sizeof(double));
  }
  s->chislo[s->top] = data;
  s->top++;
}

char *pop_str(struct Stack *s) {
  char *r = 0;
  if (s->top != 0) {
    s->top--;
    r = s->str[s->top];
  }
  return r;
}

double pop_double(struct Stack *s) {
  double r = 0;
  if (s->top != 0) {
    s->top--;
    r = s->chislo[s->top];
  }
  return r;
}

void destroy(struct Stack *s) {
  free(s->str);
  free(s->prior);
  free(s->chislo);
  free(s);
}

void add_pop(char **exit_str, char *stroka, int *j) {
  strcat(exit_str[*j], stroka);
  *j = *j + 1;
}
