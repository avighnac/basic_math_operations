#include <stdlib.h>

extern void divide_whole(const char *numerator, const char *denominator,
                         char *quotient, size_t accuracy);

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