#include <stdlib.h>
#include "../basic_math_operations.h"

extern void _multiply_whole(const char *a, const char *b, char *res, char *buf1,
                            char *buf2);

void multiply_whole(const char *a, const char *b, char *res) {
  
  size_t a_length = strlen_asm(a);
  size_t b_length = strlen_asm(b);
  char *buf1 = (char *)calloc(a_length + b_length + 1, 1);
  char *buf2 = (char *)calloc(a_length + b_length + 1, 1);
  _multiply_whole(a, b, res, buf1, buf2);
  free(buf1);
  free(buf2);
}