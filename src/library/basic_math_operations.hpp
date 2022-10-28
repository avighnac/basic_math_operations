#pragma once

#include "basic_math_operations.h"
#include <cstdlib>
#include <string>

/// @brief Recalibrated for C++.
namespace basic_math_operations {
/// @brief Adds the first two arguments and returns the result.
/// @param a The first rational number to add as a decimal.
/// @param b The second rational number to add as a decimal.
/// @return The addition of the first two arguments.
std::string add(std::string a, std::string b) {
  char *additionResult = (char *)calloc(
      std::max(a.length(), b.length()) + 3,
      1); // for the null byte, potential '-' sign, and addition carry
  ::add(a.c_str(), b.c_str(), additionResult);
  std::string answer = std::string(additionResult);
  free(additionResult);
  return answer;
}
/// @brief Subtracts the second number from the first number and returns the
/// result.
/// @param a The first rational number as a decimal.
/// @param b The rational number to subtract as a decimal.
/// @return a - b, the result of the subtraction.
std::string subtract(std::string a, std::string b) {
  char *subtractionResult = (char *)calloc(std::max(a.length(), b.length()) + 3,
                                           1); // same reason as above
  ::subtract(a.c_str(), b.c_str(), subtractionResult);
  std::string answer = std::string(subtractionResult);
  free(subtractionResult);
  return answer;
}

/// @brief Multiplies the first two arguments and returns the result.
/// @param a The first rational number as a decimal to multiply.
/// @param b The second rational number as a decimal to multiply.
/// @return The product of a and b.
std::string multiply(std::string a, std::string b) {
  char *product = (char *)calloc(a.length() + b.length() + 3, 1);
  ::multiply(a.c_str(), b.c_str(), product);
  std::string answer = std::string(product);
  free(product);
  return answer;
}

/// @brief Divides the first number by the second number and returns the result.
/// @param numerator The first rational number as a decimal to divide.
/// @param denominator The second rational number as a decimal to divide.
/// @param accuracy This is an optional argument which controls the number of
/// decimal places to calculate to.
/// @return a / b, the result of a divided by b.
std::string divide(std::string numerator, std::string denominator,
                   size_t accuracy = 10) {
  char *quotient =
      (char *)calloc(numerator.length() + denominator.length() + accuracy + 3,
                     1); // 2 for the potential negative signs in the inputs,
                         // and 2 for the same reasons mentioned above.
  ::divide(numerator.c_str(), denominator.c_str(), quotient, accuracy);
  std::string answer = std::string(quotient);
  free(quotient);
  return answer;
}

/// @brief Returns the remainder when numerator is divided by denominator.
/// @param numerator The rational numerator of the division represented as a
/// decimal.
/// @param denominator The rational denominator of the division represented as a
/// decimal.
/// @return a % b, the remainder of the division of [numerator] and
/// [denominator].
std::string mod(std::string numerator, std::string denominator) {
  char *quotient =
      (char *)calloc(numerator.length() + denominator.length() + 3, 1);
  // 2 for the potential negative signs in the inputs,
  // and 2 for the same reasons mentioned above.
  char *remainder =
      (char *)calloc(std::max(numerator.length(), denominator.length()) + 1, 1);
  divide_whole_with_remainder(numerator.c_str(), denominator.c_str(), quotient,
                              remainder);
  free(quotient);
  std::string answer = std::string(remainder);
  free(remainder);
  return answer;
}
} // namespace basic_math_operations