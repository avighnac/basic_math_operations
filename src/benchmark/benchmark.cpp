#include <basic_math_operations.h>
#include <chrono>
#include <iostream>

std::string factorial(int x) {
  std::string answer = "1";
  for (auto i = 2; i <= x; i++) {
    std::string toMultiply = std::to_string(i);
    char *partAns =
        (char *)calloc(answer.length() + toMultiply.length() + 1, 1);
    multiply(answer.c_str(), toMultiply.c_str(), partAns);
    answer = partAns;
    free(partAns);
  }

  return answer;
}

int main() {
  double time = 0;
  int x = 0;
  while (time < 1) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string s = factorial(1000);
    auto end = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::microseconds>(end - start)
                .count() *
            1e-6;
    x++;
  }

  std::cout << "1000!'s per second: " << x << '\n';
}