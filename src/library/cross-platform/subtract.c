#include "../basic_math_operations.h"

extern void addp(const char *a, const char *b, char *res);
extern void subtractp(const char *a, const char *b, char *res);

#include <string.h>

void subtract(const char *a, const char *b, char *res) {
  if (!(a[0] && b[0]))
    return;

  if (!strcmp(a, "u") || !strcmp(b, "u")) {
    strcpy(res, "u");
    return;
  }

  if (a[0] != '-' && b[0] != '-') {
    subtractp(a, b, res);
  }
  if (a[0] == '-' && b[0] != '-') {
    extern size_t strlen_asm(const char *);
    const char *new_a = a + 1;
    addp(new_a, b, res);
    for (size_t i = strlen_asm(res) - 1; i + 1 > 0; i--)
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