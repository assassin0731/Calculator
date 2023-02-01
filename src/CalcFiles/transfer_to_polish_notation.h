#ifndef SRC_TRANSFER_TO_POLISH_NOTATION_H_
#define SRC_TRANSFER_TO_POLISH_NOTATION_H_

void ToPolishNotation(char **stroka, char **exit_str, unsigned long strLen,
                      int *error);
void compare(struct Stack *s, char **exit_str, int *j, const int *i,
             char **stroka, char **symb, int prior, int *check, int k);
bool MaxNumber(char *str);

#endif  // SRC_TRANSFER_TO_POLISH_NOTATION_H_
