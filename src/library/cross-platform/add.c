#include "../basic_math_operations.h"


extern void addp(const char *a, const char *b, char *res);
extern void subtractp(const char *a, const char *b, char *res);

#include <string.h>

void add(const char *a, const char *b, char *res) {
  if (!(a[0] && b[0]))
    return;

  // Here 'u' stands for undefined
  if (!strcmp(a, "u") || !strcmp(b, "u")) {
    strcpy(res, "u");
    return;
  }

  if (a[0] != '-' && b[0] != '-') {
    addp(a, b, res);
  }
  if (a[0] == '-' && b[0] != '-') {
    const char *a_new = a + 1;
    subtractp(b, a_new, res);
  }
  if (a[0] != '-' && b[0] == '-') {
    const char *b_new = b + 1;
    subtractp(a, b_new, res);
  }
  if (a[0] == '-' && b[0] == '-') {
    const char *a_new = a + 1;
    const char *b_new = b + 1;
    addp(a_new, b_new, res);
    for (size_t i = strlen_asm(res) - 1; i + 1 > 0; i--)
      res[i + 1] = res[i];
    res[0] = '-';
  }

  remove_zeroes(res);
}