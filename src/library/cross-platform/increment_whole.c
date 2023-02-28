#include <stdbool.h>
#include <stdlib.h>
#include "../basic_math_operations.h"

void increment_whole(char **number_in) {
  char *number = *number_in;
  bool carry = true;
  size_t n = strlen_asm(number);
  for (size_t i = 0; i < n; i++) {
    if (number[i] != '9') {
      carry = false;
      break;
    }
  }

  if (carry) {
    char *new_num = (char *)calloc(n + 2, 1);
    free(number);
    new_num[0] = '1';
    for (size_t i = 0; i < n; i++)
      new_num[i + 1] = '0';
    *number_in = new_num;
    return;
  }

  number[n - 1]++;
  carry = number[n - 1] > '9';
  if (carry)
    number[n - 1] -= 10;
  for (long i = n - 2; i >= 0; i--) {
    number[i] += carry;
    carry = false;
    if (number[i] > '9') {
      number[i] -= 10;
      carry = true;
    }
  }

  return;
}