#ifndef basic_math_operations
#define basic_math_operations
/// @brief Adds the first two arguments and stores the result in the third
/// argument. Allocate enough space for the buffer (third argument) using
/// calloc.
/// @param a The first number.
/// @param b The second number.
/// @param res Where the result of the addition of the first two numbers will be
/// stored.
void add_whole(const char *a, const char *b, char *res);

/// @brief Use this function to add two numbers having the same number of
/// digits. See add_whole() for more information on how the arguments work.
/// @param a The first number.
/// @param b The second number.
/// @param res Where the result of the addition of the first two numbers will be
/// stored.
void add_whole_same_length(const char *a, const char *b, char *res);

/// @brief Subtracts the second argument from the first argument and stores the
/// result in the third argument. Allocate enough space for the buffer (third
/// argument) using calloc.
/// @param a The first number.
/// @param b The second number.
/// @param res Where a - b will be stored.
void subtract_whole(const char *a, const char *b, char *res);

/// @brief Use this function to subtract the second argument from the first
/// argument if they have the same number of digits. See subtract_whole() for
/// more information on how the arguments work.
/// @param a The first number.
/// @param b The second number.
/// @param res Where a - b will be stored.
void subtract_whole_same_length(const char *a, const char *b, char *res);
#endif