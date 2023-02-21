#include "basic_math_operations.h"
#include "remove_zeroes.h"
#include <stdlib.h>

extern void add_whole(const char *a, const char *b, char *res);
extern void add_whole_same_length(const char *a, const char *b, char *res);
extern void addp(const char *a, const char *b, char *res);
extern void add(const char *a, const char *b, char *res);

extern void subtract_whole(const char *a, const char *b, char *res);
extern void subtract_whole_same_length(const char *a, const char *b, char *res);
extern void subtractp(const char *a, const char *b, char *res);
extern void subtract(const char *a, const char *b, char *res);

extern void _multiply_whole(const char *a, const char *b, char *res, char *buf1,
                            char *buf2);
extern void multiply_whole(const char *a, const char *b, char *res);
extern void multiplyp(const char *a, const char *b, char *res);
extern void multiply(const char *a, const char *b, char *res);

extern char *_divide_whole_with_remainder(const char *numerator,
                                          const char *denominator,
                                          char *quotient, size_t bufferSize,
                                          char *buffer);
extern void divide_whole_with_remainder(const char *numerator,
                                        const char *denominator, char *quotient,
                                        char *remainder);
extern void divide_whole(const char *numerator, const char *denominator,
                         char *quotient, size_t accuracy);
extern void dividep(const char *numerator, const char *denominator,
                    char *quotient, size_t accuracy);
extern void divide(const char *a, const char *b, char *res, size_t accuracy);

extern void increment_whole(char **number_in);