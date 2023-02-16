#include "remove_zeroes.h"

void remove_zeroes(char *number) {
  char *firstPointer = number;
  extern size_t strlen(const char *);
  unsigned char negative = number[0] == '-';
  if (negative) {
    number++; // we restore this later
  }
  size_t numberLength = strlen(number);
  char *originalPointer = number;
  while (*number == '0') {
    number++;
    if (*number == '.') {
      number--;
      break;
    }
  }
  if (number - originalPointer == numberLength) // if all were '0'
    number--;
  numberLength = strlen(number);

  unsigned char decimal = 0;
  for (size_t i = 0; i < numberLength; i++) {
    if (number[i] == '.') {
      decimal = 1;
      break;
    }
  }
  if (decimal) {
    size_t to_remove = 0;
    for (size_t i = numberLength - 1; i + 1 > 0; i--) {
      if (number[i] != '0')
        break;
      to_remove++;
    }
    number[numberLength - to_remove] = '\0';
    if (number[numberLength - to_remove - 1] == '.') // to avoid stuff like "0."
      number[numberLength - to_remove - 1] = '\0';
  }

  if (negative) {
    number--; // restore the negative sign
    number[0] = '-';
    numberLength++;
  }

  char *temp = (char *)calloc(numberLength + 1, 1);
  char *origTemp = temp;
  char *realOrigTemp = temp;
  while (*number != 0) {
    *temp = *number;
    number++;
    temp++;
  }
  while (*origTemp != 0) {
    *firstPointer = *origTemp;
    origTemp++;
    firstPointer++;
  }
  *firstPointer = '\0';
  free(realOrigTemp);
}