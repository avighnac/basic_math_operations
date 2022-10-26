#ifndef _basic_math_operations_
#define _basic_math_operations_

#if defined(__cplusplus)
#define bmo_function_start extern "C"
#else
#define bmo_function_start
#endif

/// @brief Adds the first two arguments and stores the result in the third
/// argument. Allocate enough space for the buffer (third argument) using
/// calloc.
/// @param a The first whole non-negative number.
/// @param b The second whole non-negative number.
/// @param res Where the result of the addition of the first two numbers will be
/// stored.
bmo_function_start void add_whole(const char *a, const char *b, char *res);

/// @brief Use this function to add two numbers having the same number of
/// digits. See add_whole() for more information on how the arguments work.
/// @param a The first whole non-negative number.
/// @param b The second whole non-negative number.
/// @param res Where the result of the addition of the first two numbers will be
/// stored.
bmo_function_start void add_whole_same_length(const char *a, const char *b,
                                              char *res);
/// @brief Adds the first two arguments and stores the result in the third
/// argument. Allocate enough space for the buffer where the addition result
/// will be stored. (use add() for all rational numbers)
/// @param a The first non-negative rational number as a decimal.
/// @param b The second non-negative rational number as a decimal.
/// @param res Where the result of the addition of `a` and `b` will be stored.
/// @return
bmo_function_start void addp(const char *a, const char *b, char *res);

/// @brief Adds the first two arguments and stores the result in the third
/// argument. Allocate enough space for the buffer where the addition result
/// will be stored.
/// @param a The first rational number as a decimal.
/// @param b The second rational number as a decimal.
/// @param res Where a + b will be stored.
/// @return This is a void function: it does not return anything.
bmo_function_start void add(const char *a, const char *b, char *res);

/// @brief Subtracts the second argument from the first argument and stores the
/// result in the third argument. Allocate enough space for the buffer (third
/// argument) using calloc.
/// @param a The first whole non-negative number.
/// @param b The second whole non-negative number.
/// @param res Where a - b will be stored.
bmo_function_start void subtract_whole(const char *a, const char *b, char *res);

/// @brief Use this function to subtract the second argument from the first
/// argument if they have the same number of digits. See subtract_whole() for
/// more information on how the arguments work.
/// @param a The first whole non-negative number.
/// @param b The second whole non-negative number.
/// @param res Where a - b will be stored.
bmo_function_start void subtract_whole_same_length(const char *a, const char *b,
                                                   char *res);

/// @brief Subtracts the second argument from the first argument and stores the
/// result in the third argument. Allocate enough space for the third argument
/// using calloc(). (use subtract() for all rational numbers)
/// @param a The first non-negative rational number as a decimal.
/// @param b The second non-negative rational number as a decimal.
/// @param res Where a - b will be stored.
/// @return This is a void function: it does not return anything.
bmo_function_start void subtractp(const char *a, const char *b, char *res);

/// @brief Subtracts the second argument from the first argument and stores the
/// result in the third argument. Allocate enough space for the third argument
/// using calloc().
/// @param a The first rational number as a decimal.
/// @param b The second rational number as a decimal.
/// @param res Where a - b will be stored.
/// @return This is a void function: it does not return anything.
bmo_function_start void subtract(const char *a, const char *b, char *res);

/// @brief Multiplies the first argument with the second argument and stores the
/// result in the third argument. Allocate enough space for the buffer (third
/// argument) using calloc.
/// @param a The first whole non-negative number.
/// @param b The second whole non-negative number.
/// @param res Where a * b will be stored.
bmo_function_start void multiply_whole(const char *a, const char *b, char *res);

/// @brief Multiplies the first argument with the second
/// argument and stores the result in the third argument.
/// @param a The first non-negative rational number as a decimal.
/// @param b The first non-negative rational number as a decimal.
/// @param res Where a * b will be stored.
bmo_function_start void multiplyp(const char *a, const char *b, char *res);

/// @brief Multiplies the first argument with the second
/// argument and stores the result in the third argument.
/// @param a The first rational number as a decimal.
/// @param b The first rational number as a decimal.
/// @param res Where a * b will be stored.
bmo_function_start void multiply(const char *a, const char *b, char *res);

/// @brief Divides the first argument by the second argument. Stores the
/// quotient in the third argument and the remainder in the fourth argument.
/// This function is undefined when the denominator is 0.
/// @param numerator The whole non-negative numerator of the division.
/// @param denominator The while non-negative denominator of the division.
/// @param quotient The quotient of the division.
/// @param remainder The remainder of the division.
bmo_function_start void divide_whole_with_remainder(const char *numerator,
                                                    const char *denominator,
                                                    char *quotient,
                                                    char *remainder);

/// @brief Divides the first argument by the second argument with 'accuracy'
/// decimal places. Stores the quotient in the third argument. This function is
/// undefined when the denominator is 0.
/// @param numerator The whole non-negative numerator of the division.
/// @param denominator The while non-negative denominator of the division.
/// @param quotient The quotient of the division.
/// @param accuracy The number of decimal places to calculate to.
bmo_function_start void divide_whole(const char *numerator,
                                     const char *denominator, char *quotient,
                                     unsigned long accuracy);

/// @brief Divides the first argument by the second argument with 'accuracy'
/// decimal places. Stores the quotient in the third argument. This function is
/// undefined when the denominator is 0.
/// @param numerator The non-negative numerator as a decimal.
/// @param denominator The positive denominator as a decimal.
/// @param quotient The quotient of the division.
/// @param accuracy The minimum number of decimal places to calculate to.
/// @return This is a void function: it does not return anything.
bmo_function_start void dividep(const char *numerator, const char *denominator,
                                char *quotient, unsigned long accuracy);

/// @brief Divides the first argument by the second argument with 'accuracy'
/// decimal places. Stores the quotient in the third argument. This function is
/// undefined when the denominator is 0.
/// @param numerator The numerator as a decimal.
/// @param denominator The nonzero denominator as a decimal.
/// @param quotient The quotient of the division.
/// @param accuracy The minimum number of decimal places to calculate to.
/// @return This is a void function: it does not return anything.
bmo_function_start void divide(const char *numerator, const char *denominator,
                               char *quotient, unsigned long accuracy);

/// @brief Removes excess leading and trailing zeroes from a number.
/// @param number The number you want to remove zeroes from. The number is
/// overwritten.
bmo_function_start void remove_zeroes(char *number);
#endif