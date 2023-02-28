#include <stdlib.h>
#include "../basic_math_operations.h"

extern char *_divide_whole_with_remainder(const char *numerator,
                                          const char *denominator,
                                          char *quotient, size_t bufferSize,
                                          char *buffer);

void divide_whole_with_remainder(const char *numerator, const char *denominator,
                                 char *quotient, char *remainder) {
  size_t bufferSize = strlen_asm(numerator) + strlen_asm(denominator) + 2;
  char *buffer =
      (char *)calloc(5 * bufferSize + 10 * (strlen_asm(denominator) + 2) + 3, 1);
  char *rem = _divide_whole_with_remainder(numerator, denominator, quotient,
                                           bufferSize, buffer);

  extern void remove_leading_zeroes_inplace(char *);
  remove_leading_zeroes_inplace(quotient);
  remove_leading_zeroes_inplace(rem);

  for (size_t i = 0; i < strlen_asm(rem); i++)
    remainder[i] = rem[i];
  free(buffer);
}