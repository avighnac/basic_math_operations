#include "../basic_math_operations.h"

void dividep(const char *a, const char *b, char *res, size_t accuracy);

void divide(const char *a, const char *b, char *res, size_t accuracy) {
  if (!(a[0] && b[0]))
    return;

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
  extern size_t strlen_asm(const char *);
  if (a[0] == '-' && b[0] != '-') {
    const char *new_a = a + 1;
    dividep(new_a, b, res, accuracy);
    for (size_t i = strlen_asm(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }
  if (a[0] != '-' && b[0] == '-') {
    const char *new_b = b + 1;
    dividep(a, new_b, res, accuracy);
    for (size_t i = strlen_asm(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }

  remove_zeroes(res);
}