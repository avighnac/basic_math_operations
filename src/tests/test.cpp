#include <basic_math_operations.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

int test_add_mul_sub(void (*function)(const char *, const char *, char *),
                     std::vector<std::pair<std::string, std::string>> input,
                     std::vector<std::string> expected,
                     std::string functionName, std::string testName) {
  int number_tests = expected.size();
  int number_of_failed_cases = 0;

  std::cout << "Running " << number_tests << " test cases for " << testName
            << ".\n";
  for (size_t i = 0; i < number_tests; i++) {
    char *answer = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 1, 1);
    function(input[i].first.c_str(), input[i].second.c_str(), answer);
    if (std::string(answer) != expected[i]) {
      std::cout << "error in \"" << testName << "\": check " << functionName
                << "(\"" << input[i].first << "\", \"" << input[i].second
                << "\") == \"" << expected[i] << "\" failed\n";
      std::cout << "actual: \"" << answer << "\"\n";
      number_of_failed_cases++;
    }
    free(answer);
  }

  if (!number_of_failed_cases) {
    std::cout << "no errors detected in " << testName << ".\n";
  } else {
    std::cout << number_of_failed_cases << " error/s detected in " << testName
              << ".\n";
  }

  return number_of_failed_cases;
}

int main() {
  std::vector<std::pair<std::string, std::string>> input;
  std::vector<std::string> expected;
  std::string functionName, testName;
  int number_of_failed_cases = 0;

  functionName = "add_whole";
  testName = "add_whole_unit_tests";
  input = {{"2", "2"},
           {"3", "3"},
           {"2", "9"},
           {"0", "0"},
           {"3", "0"},
           {"5", "4"},
           {"9", "1"},
           {"54", "1"},
           {"99", "99"},
           {"12", "24"},
           {"123456789", "987654321"},
           {"111111111", "111111111"},
           {"54", "31"},
           {"69", "420"},
           {"9999999999", "9999999999"},
           {"9999999999", "0909090909"},
           {"98261946982146821734612734687231496127346",
            "1986327864987612837469832756872648976394"},
           {"129834691234671264213672349123648645796826625189741789647632197469"
            "182735",
            "871639874618247921657462786786123876984264"}};

  expected = {"4",
              "6",
              "11",
              "0",
              "3",
              "9",
              "10",
              "55",
              "198",
              "36",
              "1111111110",
              "222222222",
              "85",
              "489",
              "19999999998",
              "10909090908",
              "100248274847134434572082567444104145103740",
              "1298346912346712642136723491245202856714448731113992524344183213"
              "46166999"};

  number_of_failed_cases +=
      test_add_mul_sub(add_whole, input, expected, functionName, testName);

  functionName = "subtract_whole";
  testName = "subtract_whole_unit_tests";

  input.emplace_back("0", "95");
  input.emplace_back("25", "81");

  expected = {"0",
              "0",
              "-7",
              "0",
              "3",
              "1",
              "8",
              "53",
              "00",
              "-12",
              "-864197532",
              "000000000",
              "23",
              "-351",
              "0000000000",
              "9090909090",
              "96275619117159208897142901930358847150952",
              "1298346912346712642136723491227770059222083772680843268608460735"
              "92198471",
              "-95",
              "-56"};

  number_of_failed_cases +=
      test_add_mul_sub(subtract_whole, input, expected, functionName, testName);

  functionName = "multiply";
  testName = "multiply_unit_whole_numbers";

  // again, tests remain the same, but we need to change the answers
  expected = {"4",
              "9",
              "18",
              "0",
              "0",
              "20",
              "9",
              "54",
              "9801",
              "288",
              "121932631112635269",
              "12345678987654321",
              "1674",
              "28980",
              "99999999980000000001",
              "9090909089090909091",
              "1951804433585737028248503805686375012816061808451556626209259609"
              "8282166197"
              "1870324",
              "1131690939888877931854999856066286456680162706674585826798234256"
              "6686626811"
              "9444112866964275238808089400288535482040",
              "00",
              "2025"};

  number_of_failed_cases +=
      test_add_mul_sub(multiply, input, expected, functionName, testName);

  testName = "multiply_unit_rational_numbers";

  input = {
      {"1.0", "1.0"},
      {"21.2", "12.824"},
      {"3.1415926535", "9.80665"},
      {"3.1415926535", "3.1415926535"},
      {"123.871678324687", "0"},
      {"0.01", "0.01"},
      {"1.5", "1.5"},
      {"6.25", "6.25"},
      {"6.25", "2.5"},
      {"8812309324769842317698.21873698768123694",
       "219987698123.9999991209183"},
      {"1."
       "414213562373095048801688724209698078569671875376948073176679737990"
       "7324784621070388503875343276415727350138462309122970249248360",
       "1."
       "414213562373095048801688724209698078569671875376948073176679737990"
       "7324784621070388503875343276415727350138462309122970249248360"},
      {"8.3066238629180748525842627449074920102322142489556557794321883690",
       "8.3066238629180748525842627449074920102322142489556557794321883690"}};

  expected = {
      "1.00",
      "271.8688",
      "30.808499595445775",
      "9.86960440052517106225",
      "000.000000000000",
      "0.0001",
      "2.25",
      "39.0625",
      "15.625",
      "1938599643512778339818136383900441.479684605423217576299172682002",
      "1."
      "999999999999999999999999999999999999999999999999999999999999999999999999"
      "999999999999999999999999999999999999999999999999999999842030259930685943"
      "946527552197663135501198658042590050399725696788570446529764385776702628"
      "00105359605588562326683783144962689600",
      "68."
      "999999999999999999999999999999999999999999999999999999999999999375590528"
      "95735143850175491661354032696550649008965568829888016100"};

  number_of_failed_cases +=
      test_add_mul_sub(multiply, input, expected, functionName, testName);

  if (number_of_failed_cases)
    throw std::runtime_error(std::to_string(number_of_failed_cases) +
                             " test/s failed.");
}