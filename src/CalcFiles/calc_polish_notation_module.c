#include "calc.h"
#include "errors.h"
#define max_value 2000000

void GraphNumbers(double x, char **exit_str, unsigned long strLen, char find_x,
                  int *error, double *y_count, double forX, int max_x) {
  double x_count = -max_x;
  bool firstTime = true;
  if (find_x == 'x' && isnan(forX)) {
    for (int j = 0; j < N; j++) {
      if (firstTime && x_count > 0) {
        x_count = 0;
        firstTime = false;
      }
      Count(exit_str, strLen, x_count, &y_count[j], error, forX);
      x_count = x_count + x;
      if (*error != -1 || isinf(y_count[j])) {
        if (y_count[j] > max_value - 1 && *error == 10) {
          y_count[j + 1] = NAN;
          j++;
        } else {
          y_count[j] = NAN;
        }
        if (*error != Skobki) {
          *error = -1;
        }
      }
    }
  } else {
    Count(exit_str, strLen, x_count, &y_count[0], error, forX);
  }
}

void Count(char **str, int len, double x, double *c, int *error, double forX) {
  int i = 0;
  struct Stack *s;
  s = malloc(sizeof(struct Stack));
  init(s);
  double a;
  double min_eps = 0.0000000000001;
  while (i < len && *error == -1) {
    if (!(strpbrk(str[i], "*^/-+~%tgabssincoslnlogsqrt"))) {
      if (strcmp(str[i], "x") == 0 && !isnan(forX)) {
        a = forX;
      } else if (strcmp(str[i], "x") == 0) {
        a = x;
        min_eps = 0.01;
      } else {
        char *nstr = str[i];
        a = strtod(nstr, &nstr);
      }
      push_double(s, a);
    } else if (strpbrk(str[i], "tgabssincoslnlogsqrt")) {
      CheckOperation1(&a, s, c, str[i], error);
    } else {
      CheckOperation2(&a, s, c, str[i], error, min_eps);
    }
    i++;
  }
  a = pop_double(s);
  if (a != 0) *c = a;
  destroy(s);
}

void CheckOperation1(double *a, struct Stack *s, double *c, char *str,
                     int *error) {
  *a = pop_double(s);
  if (strcmp(str, "cos") == 0) {
    *a = cos(*a);
    GetY(a, s, c);
  } else if (strcmp(str, "sin") == 0) {
    *a = sin(*a);
    GetY(a, s, c);
  } else if (strcmp(str, "tg") == 0) {
    *a = tan(*a);
    if (*a > 10) {
      *a = max_value;
      *error = 10;
    }
    GetY(a, s, c);
  } else if (strcmp(str, "abs") == 0) {
    *a = fabs(*a);
    GetY(a, s, c);
  } else if (strcmp(str, "ln") == 0) {
    if (*a < 0) {
      *error = logError;
    } else {
      if (*a < eps) {
        *a = -max_value;
        *c = *a;
        push_double(s, *a);
      } else {
        *a = log(*a);
        GetY(a, s, c);
      }
    }
  } else if (strcmp(str, "sqrt") == 0) {
    if (*a < 0) {
      *error = minusSqrt;
    } else {
      *a = sqrt(*a);
      GetY(a, s, c);
    }
  } else if (strcmp(str, "asin") == 0) {
    *a = asin(*a);
    GetY(a, s, c);
  } else if (strcmp(str, "acos") == 0) {
    *a = acos(*a);
    GetY(a, s, c);
  } else if (strcmp(str, "atan") == 0) {
    *a = atan(*a);
    GetY(a, s, c);
  } else if (strcmp(str, "log") == 0) {
    if (*a < 0) {
      *error = logError;
    } else {
      if (*a < eps) {
        *a = -max_value;
        *c = *a;
        push_double(s, *a);
      } else {
        *a = log10(*a);
        GetY(a, s, c);
      }
    }
  }
}

void CheckOperation2(double *a, struct Stack *s, double *c, char *str,
                     int *error, double min_eps) {
  double b;
  *a = pop_double(s);
  if (strcmp(str, "-") == 0) {
    b = pop_double(s);
    *a = b - *a;
    GetY(a, s, c);
  } else if (strcmp(str, "+") == 0) {
    b = pop_double(s);
    *a = *a + b;
    GetY(a, s, c);
  } else if (strcmp(str, "/") == 0) {
    b = pop_double(s);
    if (fabs(*a) > min_eps) {
      *a = (double)b / *a;
      GetY(a, s, c);
    } else if (fabs(*a) > min_eps && min_eps > eps) {
      *a = max_value;
      *error = 10;
    } else {
      *error = Zero_Div;
    }
  } else if (strcmp(str, "*") == 0) {
    b = pop_double(s);
    *a = *a * b;
    GetY(a, s, c);
  } else if (strcmp(str, "^") == 0) {
    b = pop_double(s);
    *a = pow(b, *a);
    GetY(a, s, c);
  } else if (strcmp(str, "~") == 0) {
    *a = 0 - *a;
    *c = *a;
    push_double(s, *a);
  } else if (strcmp(str, "%") == 0) {
    b = pop_double(s);
    if (fabs(*a) > min_eps) {
      *a = fmod(b, *a);
      GetY(a, s, c);
    } else if (fabs(*a) > min_eps && min_eps > eps) {
      *a = max_value;
      *error = 10;
    } else {
      *error = Zero_Div;
    }
  }
}

void GetY(double *a, struct Stack *s, double *y) {
  *y = *a;
  push_double(s, *a);
}
