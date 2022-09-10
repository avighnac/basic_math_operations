#ifndef basic_math_operations
#define basic_math_operations

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

/// @brief Multiplies the first argument with the second argument and stores the
/// result in the third argument. Allocate enough space for the buffer (third
/// argument) using calloc.
/// @param a The first whole non-negative number.
/// @param b The second whole non-negative number.
/// @param res Where a * b will be stored.
bmo_function_start void multiply_whole(const char *a, const char *b, char *res);

/// @brief Divides the first argument by the second argument. Stores the
/// quotient in the third argument and the remainder in the fourth argument.
/// @param numerator The whole non-negative numerator of the division.
/// @param denominator The while non-negative denominator of the division.
/// @param quotient The quotient of the division.
/// @param remainder The remainder of the division.
bmo_function_start void divide_whole_with_remainder(const char *numerator,
                                                    const char *denominator,
                                                    char *quotient,
                                                    char *remainder);
#endif