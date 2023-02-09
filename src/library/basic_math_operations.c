#include "basic_math_operations.h"
#include "remove_zeroes.h"
#include <stdlib.h>

extern void add_whole(const char *a, const char *b, char *res);
extern void add_whole_same_length(const char *a, const char *b, char *res);
extern void addp(const char *a, const char *b, char *res);
extern void add(const char *a, const char *b, char *res);

extern void subtract_whole(const char *a, const char *b, char *res);
extern void subtract_whole_same_length(const char *a, const char *b, char *res);
void subtractp(const char *a, const char *b, char *res) {
  extern size_t strlen(const char *str);
  size_t a_len = strlen(a), b_len = strlen(b);

  char *new_a = (char *)calloc(a_len + b_len + 2, 1);
  char *new_b = (char *)calloc(a_len + b_len + 2, 1);

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
    subtract_whole(a, b, res);
    free(new_a);
    free(new_b);
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
  subtract_whole(new_a, new_b, res);

  size_t reslength = strlen(res);
  for (size_t i = 0; i < displacement; i++)
    res[reslength - i] = res[reslength - i - 1];
  if (displacement)
    res[reslength - displacement] = '.';

  free(new_a);
  free(new_b);
}
void subtract(const char *a, const char *b, char *res) {
  if (a[0] != '-' && b[0] != '-') {
    subtractp(a, b, res);
  }
  if (a[0] == '-' && b[0] != '-') {
    extern size_t strlen(const char *);
    const char *new_a = a + 1;
    addp(new_a, b, res);
    for (size_t i = strlen(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }
  if (a[0] != '-' && b[0] == '-') {
    const char *new_b = b + 1;
    addp(a, new_b, res);
  }
  if (a[0] == '-' && b[0] == '-') {
    const char *new_b = b + 1;
    const char *new_a = a + 1;
    subtractp(new_b, new_a, res);
  }

  remove_zeroes(res);
}

extern void _multiply_whole(const char *a, const char *b, char *res, char *buf1,
                            char *buf2);
extern void multiply_whole(const char *a, const char *b, char *res);

void multiplyp(const char *a, const char *b, char *res) {
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
void multiply(const char *a, const char *b, char *res) {
  if (a[0] != '-' && b[0] != '-') {
    multiplyp(a, b, res);
  }
  if (a[0] == '-' && b[0] == '-') {
    const char *a_new = a + 1;
    const char *b_new = b + 1;
    multiplyp(a_new, b_new, res);
  }
  extern size_t strlen(const char *);
  if (a[0] == '-' && b[0] != '-') {
    const char *a_new = a + 1;
    multiplyp(a_new, b, res);
    for (size_t i = strlen(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }
  if (a[0] != '-' && b[0] == '-') {
    const char *b_new = b + 1;
    multiplyp(a, b_new, res);
    for (size_t i = strlen(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }

  remove_zeroes(res);
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
  size_t denominator_length = strlen(denominator);
  size_t modified_numerator_length = numerator_length + accuracy;
  char *modified_numerator = (char *)calloc(modified_numerator_length + 1, 1);

  for (size_t i = 0; i < numerator_length; i++)
    modified_numerator[i] = numerator[i];
  for (size_t i = numerator_length; i < accuracy + numerator_length; i++)
    modified_numerator[i] = '0';

  size_t bufferSize = modified_numerator_length + denominator_length + 2;
  char *buffer =
      (char *)calloc(5 * bufferSize + 10 * (denominator_length + 2) + 3, 1);
  char *rem = _divide_whole_with_remainder(modified_numerator, denominator,
                                           quotient, bufferSize, buffer);

  size_t quotient_length = strlen(quotient);
  for (size_t i = 0; i < accuracy; i++)
    quotient[quotient_length - i] = quotient[quotient_length - i - 1];
  quotient[quotient_length - accuracy] = '.';

  free(buffer);
  free(modified_numerator);
}
void dividep(const char *numerator, const char *denominator, char *quotient,
             size_t accuracy) {
  extern size_t strlen(const char *str);
  size_t numerator_length = strlen(numerator);
  size_t denominator_length = strlen(denominator);
  size_t max_length = numerator_length;
  if (denominator_length > numerator_length)
    max_length = denominator_length;
  max_length += accuracy;
  char *numerator_copy = (char *)calloc(max_length + 1, 1);
  char *denominator_copy = (char *)calloc(max_length + 1, 1);

  size_t ptr1 = 0, ptr2 = 0;
  int n1 = 0, n2 = 0;
  unsigned int flag = 0;
  for (size_t i = 0; i < numerator_length; i++) {
    if (flag)
      n1++;
    if (numerator[i] == '.')
      flag = 1;
    else
      numerator_copy[ptr1++] = numerator[i];
  }

  flag = 0;
  ptr2 = 0;
  for (size_t i = 0; i < denominator_length; i++) {
    if (flag)
      n2++;
    if (denominator[i] == '.')
      flag = 1;
    else
      denominator_copy[ptr2++] = denominator[i];
  }

  if (n2 < n1)
    for (size_t i = 0; i < n1 - n2; i++)
      denominator_copy[ptr2++] = '0';
  if (n1 < n2)
    for (size_t i = 0; i < n2 - n1; i++)
      numerator_copy[ptr1++] = '0';

  divide_whole(numerator_copy, denominator_copy, quotient, accuracy);
  free(numerator_copy);
  free(denominator_copy);
}
void divide(const char *a, const char *b, char *res, size_t accuracy) {
  // a is the numerator and b is the denominator
  // I've used different names to shorten the code
  if (a[0] != '-' && b[0] != '-') {
    dividep(a, b, res, accuracy);
  }
  if (a[0] == '-' && b[0] == '-') {
    const char *new_a = a + 1;
    const char *new_b = b + 1;
    dividep(new_a, new_b, res, accuracy);
  }
  extern size_t strlen(const char *);
  if (a[0] == '-' && b[0] != '-') {
    const char *new_a = a + 1;
    dividep(new_a, b, res, accuracy);
    for (size_t i = strlen(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }
  if (a[0] != '-' && b[0] == '-') {
    const char *new_b = b + 1;
    dividep(a, new_b, res, accuracy);
    for (size_t i = strlen(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }

  remove_zeroes(res);
}

extern void increment_whole(char **number_in);