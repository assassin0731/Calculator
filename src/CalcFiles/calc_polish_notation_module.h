#ifndef SRC_CALC_POLISH_NOTATION_MODULE_H_
#define SRC_CALC_POLISH_NOTATION_MODULE_H_

void GraphNumbers(double x, char **exit_str, unsigned long strLen, char find_x,
                  int *error, double *y_count, double forX, int max_x);
void Count(char **str, int len, double x, double *c, int *error, double forX);
void CheckOperation1(double *a, struct Stack *s, double *c, char *str,
                     int *error);
void CheckOperation2(double *a, struct Stack *s, double *c, char *str,
                     int *error, double min_eps);
bool MaxNumber(char *str);
void GetY(double *a, struct Stack *s, double *y);

#endif  // SRC_CALC_POLISH_NOTATION_MODULE_H_
