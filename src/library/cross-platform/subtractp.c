#include <stdlib.h>
#include <string.h>

extern void subtract_whole(const char *a, const char *b, char *res);

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