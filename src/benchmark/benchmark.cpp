#include "../library/basic_math_operations.hpp"
#include <chrono>
#include <random>
#include <iostream>

std::string factorial(int x) {
  std::string answer = "1";
  for (auto i = 2; i <= x; i++) {
    std::string toMultiply = std::to_string(i);
    char *partAns =
        (char *)calloc(answer.length() + toMultiply.length() + 1, sizeof(char));
    multiply(answer.c_str(), toMultiply.c_str(), partAns);
    answer = partAns;
    free(partAns);
  }

  return answer;
}

std::string add_random(size_t max_digits) {
  // Generate two random strings of [0,9]'s with [max_digits - 20] +/- 20 digits

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 20);

  size_t digits = max_digits - dis(gen);
  std::string a, b;
  for (size_t i = 0; i < digits; i++) {
    a += std::to_string(dis(gen));
  }
  digits = max_digits - dis(gen);
  for (size_t i = 0; i < digits; i++) {
    b += std::to_string(dis(gen));
  }

  char *ans = (char *)calloc(a.length() + b.length() + 1, sizeof(char));
  multiply(a.c_str(), b.c_str(), ans);
  std::string answer = ans;
  free(ans);
  return answer;
}

int main() {
  #define MAX_TIME 5

  double time = 0;
  int x = 0;

  while (time < MAX_TIME) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string s = add_random(200);
    auto end = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count() *
            1e-6;
    x++;
  }

  std::cout << "Random multiplications (200 digits max) per second: " << x / MAX_TIME << '\n';
}