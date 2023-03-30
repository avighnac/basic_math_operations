#pragma once

#include "basic_math_operations.h"
#include <cstdlib>
#include <string>
#include <random>
#ifdef _WIN32
#include <ostream>
#endif

/// @brief Wrapper for C++.
namespace basic_math_operations {
/// @brief Adds the first two arguments and returns the result.
/// @param a The first rational number to add as a decimal.
/// @param b The second rational number to add as a decimal.
/// @return The addition of the first two arguments.
std::string add(std::string a, std::string b);

/// @brief Subtracts the second number from the first number and returns the
/// result.
/// @param a The first rational number as a decimal.
/// @param b The rational number to subtract as a decimal.
/// @return a - b, the result of the subtraction.
std::string subtract(std::string a, std::string b);

/// @brief Multiplies the first two arguments and returns the result.
/// @param a The first rational number as a decimal to multiply.
/// @param b The second rational number as a decimal to multiply.
/// @return The product of a and b.
std::string multiply(std::string a, std::string b);

/// @brief Divides the first number by the second number and returns the result.
/// @param numerator The first rational number as a decimal to divide.
/// @param denominator The second rational number as a decimal to divide.
/// @param accuracy This is an optional argument which controls the number of
/// decimal places to calculate to.
/// @return a / b, the result of a divided by b.
std::string divide(std::string numerator, std::string denominator,
                   size_t accuracy);

/// @brief Returns the remainder when numerator is divided by denominator.
/// @param numerator The rational numerator of the division represented as a
/// decimal.
/// @param denominator The rational denominator of the division represented as a
/// decimal.
/// @return a % b, the remainder of the division of [numerator] and
/// [denominator].
std::string mod(std::string numerator, std::string denominator);

// constant that controls division accuracy
inline size_t DIVISION_ACCURACY = 10;

// BMONum
class BMONum {
public:
  std::string number;

  BMONum();
  BMONum(std::string number);
  BMONum(const char *number);

  BMONum operator+(BMONum n);
  BMONum operator-(BMONum n);
  BMONum operator*(BMONum n);
  BMONum operator/(BMONum n);
  BMONum operator%(BMONum n);

  bool operator<(BMONum n);
  bool operator>(BMONum n);
  bool operator==(BMONum n);
  bool operator>=(BMONum n);

  friend std::ostream &operator<<(std::ostream &os, const BMONum &n) {
    os << n.number;
    return os;
  }
};

BMONum random(unsigned long long decimal_places);
} // namespace basic_math_operations