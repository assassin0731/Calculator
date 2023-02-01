#ifndef SRC_CALC_H_
#define SRC_CALC_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alib_dynamic_module.h"
#include "calc_polish_notation_module.h"
#include "read_term_module.h"
#include "transfer_to_polish_notation.h"

#define eps 0.0000001
#define M 25
#define N 10000

void calculation(char *string, char *result, double forX, int max_x,
                 double *mas_y);
char **memory(int len);
void MemoryFree(char **str, int len);

#endif  // SRC_CALC_H_
