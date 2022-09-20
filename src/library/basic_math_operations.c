#include "basic_math_operations.h"
#include <assert.h>
#include <stdlib.h>

extern void add_whole(const char *a, const char *b, char *res);
extern void add_whole_same_length(const char *a, const char *b, char *res);

extern void subtract_whole(const char *a, const char *b, char *res);
extern void subtract_whole_same_length(const char *a, const char *b, char *res);

extern void _multiply_whole(const char *a, const char *b, char *res, char *buf1,
                            char *buf2);
void multiply(const char *a, const char *b, char *res) {
  extern size_t strlen(const char *str);
  size_t a_length = strlen(a);
  size_t b_length = strlen(b);
  char *a_copy = (char *)calloc(a_length + 1, 1);
  char *b_copy = (char *)calloc(b_length + 1, 1);
  size_t ptr = 0;
  int displacement = 0;
  unsigned char flag = 0;
  for (size_t i = 0; i < a_length; i++) {
    if (flag == 1)
      displacement++;
    if (a[i] == '.')
      flag = 1;
    else {
      a_copy[ptr] = a[i];
      ptr++;
    }
  }
  ptr = 0;
  flag = 0;
  for (size_t i = 0; i < b_length; i++) {
    if (flag == 1)
      displacement++;
    if (b[i] == '.')
      flag = 1;
    else {
      b_copy[ptr] = b[i];
      ptr++;
    }
  }

  size_t bufsize = strlen(a) + strlen(b) + 1;
  char *buf1 = (char *)calloc(bufsize, 1);
  char *buf2 = (char *)calloc(bufsize, 1);
  _multiply_whole(a_copy, b_copy, res, buf1, buf2);

  size_t reslength = strlen(res);
  for (size_t i = 0; i < displacement; i++)
    res[reslength - i] = res[reslength - i - 1];
  if (displacement)
    res[reslength - displacement] = '.';

  free(buf1);
  free(buf2);
  free(a_copy);
  free(b_copy);
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

  extern void remove_leading_zeroes_inplace(char *);
  remove_leading_zeroes_inplace(quotient);
  remove_leading_zeroes_inplace(rem);

  for (size_t i = 0; i < strlen(rem); i++)
    remainder[i] = rem[i];
  free(buffer);
}