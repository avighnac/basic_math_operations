#include <stdlib.h>
#include <string.h>

extern char *_divide_whole_with_remainder(const char *numerator,
                                          const char *denominator,
                                          char *quotient, size_t bufferSize,
                                          char *buffer);

void divide_whole(const char *numerator, const char *denominator,
                  char *quotient, size_t accuracy) {

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