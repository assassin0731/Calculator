#include "calc.h"
#include "errors.h"

void ReadTerm(char *stroka, char *find_x, int *error) {
  char remember_prev[2];
  remember_prev[0] = '\0';
  remember_prev[1] = '\0';
  int i = 0;
  while (i < (int)strlen(stroka) && stroka[i] != '\0' && *error == -1) {
    if (i < (int)strlen(stroka) && stroka[i] == 'x') {
      *find_x = 'x';
    }
    char to_str[2];
    to_str[0] = stroka[i];
    to_str[1] = '\0';
    if ((strpbrk(to_str, "-~+^/*%") && strpbrk(remember_prev, "-~+^/*%")) ||
        (i == 0 && strpbrk(to_str, "+^/*%")) ||
        (strpbrk(to_str, "+^/*%") && strpbrk(remember_prev, "(")) ||
        (!strpbrk(to_str, ")*-+/^%") && strpbrk(remember_prev, ")")) ||
        (strpbrk(to_str, "(") && strpbrk(remember_prev, "0123456789x")) ||
        (strpbrk(to_str, "x") && strpbrk(remember_prev, "0123456789x")) ||
        (strpbrk(to_str, "0123456789x") && strpbrk(remember_prev, "x")) ||
        (!strpbrk(to_str, "0123456789x)") && i == (int)strlen(stroka) - 1)) {
      *error = Zapis;
    }
    remember_prev[0] = stroka[i];
    i++;
  }
}

void CreateNewStr(char *stroka, char **new_str, int *a, int *error) {
  int i = 0, j = 0;
  char *str = malloc(2);
  str[1] = '\0';
  while (stroka[j] && *error == -1) {
    if (stroka[j] == '.') {
      *error = Zapis;
    } else {
      if (stroka[j] >= '0' && stroka[j] <= '9') {
        bool checkDot = false;
        while (stroka[j] >= '0' && stroka[j] <= '9') {
          MakeStr(new_str, str, stroka, 1, &j, &i);
          if (stroka[j] == '.' && !checkDot) {
            checkDot = true;
            MakeStr(new_str, str, stroka, 1, &j, &i);
          } else if (stroka[j] == '.' && checkDot) {
            *error = Zapis;
            break;
          }
        }
      } else if ((stroka[j] == 'a' && stroka[j + 1] == 'b') ||
                 stroka[j] == 'c' ||
                 (stroka[j] == 's' && stroka[j + 1] == 'i') ||
                 (stroka[j] == 'l' && stroka[j + 1] == 'o')) {
        MakeStr(new_str, str, stroka, 3, &j, &i);
      } else if (stroka[j] == 't' || stroka[j] == 'l') {
        MakeStr(new_str, str, stroka, 2, &j, &i);
      } else if (stroka[j] == 's' || stroka[j] == 'a') {
        MakeStr(new_str, str, stroka, 4, &j, &i);
      } else if (j != 0) {
        if (stroka[j] == '-' && stroka[j - 1] == '(') {
          stroka[j] = '~';
          MakeStr(new_str, str, stroka, 1, &j, &i);
        } else {
          MakeStr(new_str, str, stroka, 1, &j, &i);
        }
      } else {
        MakeStr(new_str, str, stroka, 1, &j, &i);
      }
      i++;
    }
  }
  *a = i;
  free(str);
}

void MakeStr(char **new_str, char *str, const char *stroka, int k, int *j,
             const int *i) {
  for (int l = 0; l < k; l++) {
    str[0] = stroka[*j];
    strcat(new_str[*i], str);
    *j = *j + 1;
  }
}
