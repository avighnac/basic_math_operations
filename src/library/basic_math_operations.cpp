#include "basic_math_operations.hpp"

std::string basic_math_operations::add(std::string a, std::string b) {
  char *additionResult = (char *)calloc(
      a.length() + b.length() + 3,
      1); // for the null byte, potential '-' sign, and addition carry
  ::add(a.c_str(), b.c_str(), additionResult);
  std::string answer = std::string(additionResult);
  free(additionResult);
  return answer;
}

std::string basic_math_operations::subtract(std::string a, std::string b) {
  char *subtractionResult =
      (char *)calloc(a.length() + b.length() + 3, 1); // same reason as above
  ::subtract(a.c_str(), b.c_str(), subtractionResult);
  std::string answer = std::string(subtractionResult);
  free(subtractionResult);
  return answer;
}

std::string basic_math_operations::multiply(std::string a, std::string b) {
  char *product = (char *)calloc(a.length() + b.length() + 3, 1);
  ::multiply(a.c_str(), b.c_str(), product);
  std::string answer = std::string(product);
  free(product);
  return answer;
}

std::string basic_math_operations::divide(std::string numerator,
                                          std::string denominator,
                                          size_t accuracy) {
  char *quotient =
      (char *)calloc(numerator.length() + denominator.length() + accuracy + 3,
                     1); // 2 for the potential negative signs in the inputs,
                         // and 2 for the same reasons mentioned above.
  ::divide(numerator.c_str(), denominator.c_str(), quotient, accuracy);
  std::string answer = std::string(quotient);
  free(quotient);
  return answer;
}

std::string basic_math_operations::mod(std::string numerator,
                                       std::string denominator) {
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

basic_math_operations::BMONum::BMONum() { number = "0"; }
basic_math_operations::BMONum::BMONum(std::string number) {
  this->number = number;
}
basic_math_operations::BMONum::BMONum(const char *number) {
  this->number = number;
}

basic_math_operations::BMONum
basic_math_operations::BMONum::operator+(BMONum n) {
  BMONum answer;
  answer.number = add(number, n.number);
  return answer;
}
basic_math_operations::BMONum
basic_math_operations::BMONum::operator-(BMONum n) {
  BMONum answer;
  answer.number = subtract(number, n.number);
  return answer;
}
basic_math_operations::BMONum
basic_math_operations::BMONum::operator*(BMONum n) {
  BMONum answer;
  answer.number = multiply(number, n.number);
  return answer;
}
basic_math_operations::BMONum
basic_math_operations::BMONum::operator/(BMONum n) {
  BMONum answer;
  answer.number = divide(number, n.number, DIVISION_ACCURACY);
  return answer;
}
basic_math_operations::BMONum
basic_math_operations::BMONum::operator%(BMONum n) {
  BMONum answer;
  answer.number = mod(number, n.number);
  return answer;
}

bool basic_math_operations::BMONum::operator<(basic_math_operations::BMONum n) {
  // return true if this < n, else false
  // this < n ==> this - n < 0

  std::string difference = subtract(number, n.number);
  return difference[0] == '-';
}
bool basic_math_operations::BMONum::operator>(basic_math_operations::BMONum n) {
  // return true if this > n, else false
  // this > n ==> n < this

  return n < *this;
}
bool basic_math_operations::BMONum::operator==(
    basic_math_operations::BMONum n) {
  return number == n.number;
}
bool basic_math_operations::BMONum::operator>=(
    basic_math_operations::BMONum n) {
  return *this > n || *this == n;
}

basic_math_operations::BMONum basic_math_operations::random(unsigned long long decimal_places) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 9);
  std::string number = "";
  for (unsigned long long i = 0; i < decimal_places; ++i) {
    number += std::to_string(dis(gen));
  }
  if (dis(gen) % 2 == 0) {
    number = "-" + number;
  }
  return basic_math_operations::BMONum(number);
}