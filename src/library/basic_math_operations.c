#include "basic_math_operations.h"
#include <assert.h>
#include <stdlib.h>

extern void add_whole(const char *a, const char *b, char *res);
extern void add_whole_same_length(const char *a, const char *b, char *res);
void add(const char *a, const char *b, char *res) {
  extern size_t strlen(const char *str);
  size_t a_len = strlen(a), b_len = strlen(b);
  size_t max_len = a_len;
  if (b_len > a_len)
    max_len = b_len;

  char *new_a = (char *)calloc(max_len + 1, 1);
  char *new_b = (char *)calloc(max_len + 1, 1);

  size_t ptr1 = 0, ptr2 = 0;
  int n1 = 0, n2 = 0;
  unsigned int flag = 0;
  for (size_t i = 0; i < a_len; i++) {
    if (flag)
      n1++;
    if (a[i] == '.')
      flag = 1;
    else
      new_a[ptr1++] = a[i];
  }

  flag = 0;
  ptr2 = 0;
  for (size_t i = 0; i < b_len; i++) {
    if (flag)
      n2++;
    if (b[i] == '.')
      flag = 1;
    else
      new_b[ptr2++] = b[i];
  }

  if (n1 == 0 && n2 == 0) {
    add_whole(a, b, res);
    return;
  }

  int displacement = n1;
  if (n1 < n2) {
    displacement = n2;
    for (int i = 0; i < n2 - n1; i++)
      new_a[ptr1++] = '0';
  } else if (n2 < n1) {
    displacement = n1;
    for (int i = 0; i < n1 - n2; i++)
      new_b[ptr2++] = '0';
  }
  add_whole(new_a, new_b, res);

  size_t reslength = strlen(res);
  for (size_t i = 0; i < displacement; i++)
    res[reslength - i] = res[reslength - i - 1];
  if (displacement)
    res[reslength - displacement] = '.';

  free(new_a);
  free(new_b);
}

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

void divide_whole(const char *numerator, const char *denominator,
                  char *quotient, size_t accuracy) {
  extern size_t strlen(const char *str);

  size_t numerator_length = strlen(numerator);
  size_t modified_numerator_length = numerator_length + accuracy;
  char *modified_numerator = (char *)calloc(numerator_length + accuracy + 1, 1);

  for (size_t i = 0; i < numerator_length; i++)
    modified_numerator[i] = numerator[i];
  for (size_t i = numerator_length; i < accuracy + numerator_length; i++)
    modified_numerator[i] = '0';

  size_t bufferSize = modified_numerator_length + strlen(denominator) + 2;
  char *buffer =
      (char *)calloc(5 * bufferSize + 10 * (strlen(denominator) + 2) + 3, 1);
  char *rem = _divide_whole_with_remainder(modified_numerator, denominator,
                                           quotient, bufferSize, buffer);

  size_t quotient_length = strlen(quotient);
  for (size_t i = 0; i < accuracy; i++)
    quotient[quotient_length - i] = quotient[quotient_length - i - 1];
  quotient[quotient_length - accuracy] = '.';

  free(buffer);
  free(modified_numerator);
}