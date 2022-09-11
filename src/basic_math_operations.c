#include "basic_math_operations.h"
#include <stdlib.h>

extern void add_whole(const char *a, const char *b, char *res);
extern void add_whole_same_length(const char *a, const char *b, char *res);

extern void subtract_whole(const char *a, const char *b, char *res);
extern void subtract_whole_same_length(const char *a, const char *b, char *res);

extern void _multiply_whole(const char *a, const char *b, char *res, char *buf1,
                            char *buf2);
void multiply_whole(const char *a, const char *b, char *res) {
  extern size_t strlen(const char *str);
  size_t a_len = strlen(a);
  size_t b_len = strlen(b);
  char *buf1 = (char *)calloc(a_len + b_len + 1, 1);
  char *buf2 = (char *)calloc(a_len + b_len + 1, 1);
  _multiply_whole(a, b, res, buf1, buf2);
  free(buf1);
  free(buf2);
}

extern char *_divide_whole_with_remainder(const char *numerator,
                                          const char *denominator,
                                          char *quotient, size_t bufferSize,
                                          char *buffer);
void divide_whole_with_remainder(const char *numerator, const char *denominator,
                                 char *quotient, char *remainder) {
  extern size_t strlen(const char *str);
  size_t bufferSize = strlen(numerator) + strlen(denominator) + 2;
  char *buffer =
      (char *)calloc(5 * bufferSize + 10 * (strlen(denominator) + 2) + 3, 1);
  char *rem = _divide_whole_with_remainder(numerator, denominator, quotient,
                                           bufferSize, buffer);
  for (size_t i = 0; i < strlen(rem); i++)
    remainder[i] = rem[i];
  free(buffer);
  free(rem);
}