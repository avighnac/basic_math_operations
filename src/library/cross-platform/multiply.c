#include "../remove_zeroes.h"

extern void multiplyp(const char *a, const char *b, char *res);

void multiply(const char *a, const char *b, char *res) {
  if (a[0] == '\0' || b[0] == '\0')
    return;

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