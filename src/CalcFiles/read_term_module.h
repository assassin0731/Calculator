#ifndef SRC_READ_TERM_MODULE_H_
#define SRC_READ_TERM_MODULE_H_

void ReadTerm(char *stroka, char *find_x, int *error);
void CreateNewStr(char *stroka, char **new_str, int *a, int *error);
void MakeStr(char **new_str, char *str, const char *stroka, int k, int *j,
             const int *i);

#endif  // SRC_READ_TERM_MODULE_H_
