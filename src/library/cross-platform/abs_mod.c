#include "../basic_math_operations.h"
#include <stdlib.h>
#include <string.h>

char *abs_mod(const char *a_in, const char *b_in)
{
    char *a = (char *)a_in;
    char *b = (char *)b_in;

    if (*a == '-')
    {
        ++a;
    }
    if (*b == '-')
    {
        ++b;
    }

    size_t max = strlen(a) > strlen(b) ? strlen(a) : strlen(b);
    char *quotient = (char *)calloc(strlen(a) + strlen(b) + 3, 1);
    char *remainder = (char *)calloc(max + 1, 1);
    divide_whole_with_remainder(a, b, quotient, remainder);

    free(quotient);
    return remainder;
}