#include "calc.h"
#include "errors.h"

void ToPolishNotation(char **stroka, char **exit_str, unsigned long strLen,
                      int *error) {
  struct Stack *s;
  s = malloc(sizeof(struct Stack));
  init(s);
  char *symb[19] = {"-",    "+",    "*",    "/",   "^",  "~",
                    "cos",  "sin",  "tg",   "abs", "ln", "sqrt",
                    "acos", "asin", "atan", "log", "%"};
  int prior[19] = {1, 1, 2, 2, 4, 3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 2};
  int i = 0, j = 0;
  int check = 0;
  int counter_left = 0;
  char remember_prev[2];
  remember_prev[0] = '\0';
  remember_prev[1] = '\0';
  while (strLen && *error == -1) {
    if (MaxNumber(stroka[i])) {
      *error = bigNum;
    } else {
      strLen--;
      if (i > 0) {
        remember_prev[0] = stroka[i - 1][0];
      }
      if (strcmp(stroka[i], "(") == 0) {
        counter_left++;
        push_str(s, stroka[i], 0);
        check = 1;
      } else {
        for (int k = 0; k < 17 && check != 1; k++) {
          compare(s, exit_str, &j, &i, stroka, symb, prior[k], &check, k);
        }
      }
      if (strcmp(stroka[i], ")") == 0) {
        if (counter_left == 0 || strpbrk(remember_prev, "(+*%/")) {
          *error = Skobki;
        } else {
          while (strcmp(s->str[s->top - 1], "(") != 0) {
            add_pop(exit_str, pop_str(s), &j);
          }
          check = 1;
          pop_str(s);
        }
        counter_left--;
      }
      if (*error == -1) {
        if (check == 0) {
          add_pop(exit_str, stroka[i], &j);
        }
        check = 0;
        i++;
      }
    }
  }
  while (s->top != 0) {
    add_pop(exit_str, pop_str(s), &j);
  }
  destroy(s);
  if (counter_left > 0) {
    *error = Skobki;
  }
}

void compare(struct Stack *s, char **exit_str, int *j, const int *i,
             char **stroka, char **symb, int prior, int *check, int k) {
  if (!strcmp(stroka[*i], symb[k]) && *check == 0) {
    while (s->top - 1 >= 0 && s->prior[s->top - 1] >= prior) {
      strcpy(exit_str[*j], pop_str(s));
      *j = *j + 1;
    }
    *check = 1;
    push_str(s, stroka[*i], prior);
  } else {
    *check = 0;
  }
}

bool MaxNumber(char *str) {
  char max_double[17] = "900719925474099";
  char copy[256] = {'\0'};
  int i = 0;
  for (; i < (int)strlen(str) && str[i] != '.'; i++) {
    copy[i] = str[i];
  }
  copy[i] = '\0';
  bool return_value = 0;
  if (strlen(copy) > strlen(max_double)) {
    return_value = 1;
  } else if (strlen(copy) < strlen(max_double)) {
    return_value = 0;
  } else {
    i = 0;
    while (return_value == 0 && i < (int)strlen(copy)) {
      if (copy[i] > max_double[i]) {
        return_value = 1;
      }
      i++;
    }
    if (i == (int)strlen(copy) && strlen(str) > strlen(copy)) {
      return_value = 1;
    }
  }
  return return_value;
}
