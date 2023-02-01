#include "calc.h"

#include "errors.h"

char *ErrorNames[] = {"Деление на 0",
                      "Неправильно расставлены скобки",
                      "Ошибка в записи",
                      "Отрицательный корень",
                      "Несуществующий логарифм",
                      "Слишком большое число"};

void calculation(char *string, char *result, double forX, int max_x,
                 double *y_count) {
  double x = 2. * max_x / N;
  char find_x = '\0';
  int error = -1;
  char *stroka = string;
  ReadTerm(stroka, &find_x, &error);
  if (error == -1) {
    char **new_str = memory(strlen(stroka));
    int i = 0;
    CreateNewStr(stroka, new_str, &i, &error);
    if (error == -1) {
      int strLen = i;
      char **exit_str = memory(strLen);
      ToPolishNotation(new_str, exit_str, strLen, &error);
      GraphNumbers(x, exit_str, strLen, find_x, &error, y_count, forX, max_x);
      MemoryFree(exit_str, strLen);
    }
    MemoryFree(new_str, strlen(stroka));
  }
  if (error != -1) {
    strcat(result, ErrorNames[error]);
  } else if (!isnan(forX)) {
    sprintf(result, "%lf", y_count[0]);
  }
}

void MemoryFree(char **str, int len) {
  for (int i = 0; i < len; i++) {
    free(str[i]);
  }
  free(str);
}

char **memory(int len) {
  char **str = malloc(len * sizeof(char *));
  for (int i = 0; i < len; i++) {
    str[i] = malloc(len * sizeof(char));
    str[i][0] = '\0';
  }
  return str;
}
