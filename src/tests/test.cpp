#include "color.hpp"
#include "get_current_directory.hpp"
#include <algorithm>
#include <basic_math_operations.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

int test_add_mul_sub(void (*function)(const char *, const char *, char *),
                     std::vector<std::pair<std::string, std::string>> input,
                     std::vector<std::string> expected,
                     std::string functionName, std::string testName) {
  int number_tests = expected.size();
  int number_of_failed_cases = 0;

  std::cout << "Running " << color(std::to_string(number_tests), "Magenta")
            << " test cases for " << color(testName, "Cyan") << ".\n";
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < number_tests; i++) {
    char *answer = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 1, 1);
    function(input[i].first.c_str(), input[i].second.c_str(), answer);
    if (std::string(answer) != expected[i]) {
      std::cout << "error in \"" << color(testName, "Cyan") << "\": check "
                << functionName << "(\"" << input[i].first << "\", \""
                << input[i].second << "\") == \"" << expected[i]
                << "\" failed\n";
      std::cout << "actual: \"" << answer << "\"\n";
      number_of_failed_cases++;
    }
    free(answer);
  }
  auto end = std::chrono::high_resolution_clock::now();

  if (!number_of_failed_cases) {
    std::cout << color("No errors detected", "Green") << " in "
              << color(testName, "Yellow") << ". (finished in "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                         .count() *
                     1e-3
              << " \u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in "
              << color(testName, "Cyan") << ".\n";
  }

  return number_of_failed_cases;
}

int test_div(void (*divide_func)(const char *, const char *, char *, char *),
             std::vector<std::pair<std::string, std::string>> input,
             std::vector<std::pair<std::string, std::string>> expected,
             std::string functionName, std::string testName) {
  int number_tests = expected.size();
  int number_of_failed_cases = 0;

  std::cout << "Running " << color(std::to_string(number_tests), "Magenta")
            << " test cases for " << color(testName, "Cyan") << ".\n";
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < number_tests; i++) {
    char *quotient = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 1, 1);
    char *remainder = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 1, 1);
    divide_func(input[i].first.c_str(), input[i].second.c_str(), quotient,
                remainder);
    if (std::string(quotient) != expected[i].first ||
        std::string(remainder) != expected[i].second) {
      std::cout << "error in \"" << color(testName, "Cyan") << "\": check "
                << functionName << "(\"" << input[i].first << "\", \""
                << input[i].second << "\") == (\"" << expected[i].first
                << "\", \"" << expected[i].second << "\") failed\n";
      std::cout << "actual: (\"" << quotient << "\", \"" << remainder
                << "\")\n";
      number_of_failed_cases++;
    }
    free(quotient);
    free(remainder);
  }
  auto end = std::chrono::high_resolution_clock::now();

  if (!number_of_failed_cases) {
    std::cout << color("No errors detected", "Green") << " in "
              << color(testName, "Yellow") << ". (finished in "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                         .count() *
                     1e-3
              << " \u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in "
              << color(testName, "Cyan") << ".\n";
  }

  return number_of_failed_cases;
}

int test_rlz(void (*rlz)(char *), std::vector<std::string> input,
             std::vector<std::string> expected, std::string functionName,
             std::string testName) {
  int number_tests = expected.size();
  int number_of_failed_cases = 0;

  std::cout << "Running " << color(std::to_string(number_tests), "Magenta")
            << " test cases for " << color(testName, "Cyan") << ".\n";
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < number_tests; i++) {
    char *number = (char *)calloc(input[i].length() + 1, 1);
    strcpy(number, input[i].c_str());
    rlz(number);
    if (std::string(number) != expected[i]) {
      std::cout << "error in \"" << color(testName, "Cyan") << "\": check "
                << functionName << "(\"" << input[i] << "\") == \""
                << expected[i] << "\" failed\n";
      std::cout << "actual: \"" << number << "\"\n";
      number_of_failed_cases++;
    }
    free(number);
  }
  auto end = std::chrono::high_resolution_clock::now();

  if (!number_of_failed_cases) {
    std::cout << color("No errors detected", "Green") << " in "
              << color(testName, "Yellow") << ". (finished in "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                         .count() *
                     1e-3
              << " \u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in "
              << color(testName, "Cyan") << ".\n";
  }

  return number_of_failed_cases;
}

int test_mdiv(void (*divide)(const char *, const char *, char *, size_t),
              std::vector<std::pair<std::string, std::string>> input,
              std::vector<std::string> expected, std::string functionName,
              std::string testName) {
  int number_tests = expected.size();
  int number_of_failed_cases = 0;

  std::cout << "Running " << color(std::to_string(number_tests), "Magenta")
            << " test cases for " << color(testName, "Cyan") << ".\n";
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < number_tests; i++) {
    char *answer = (char *)calloc(
        input[i].first.length() + input[i].second.length() + 21, 1);
    divide(input[i].first.c_str(), input[i].second.c_str(), answer, 20);
    if (std::string(answer) != expected[i]) {
      std::cout << "error in \"" << color(testName, "Cyan") << "\": check "
                << functionName << "(\"" << input[i].first << "\", \""
                << input[i].second << "\") == \"" << expected[i]
                << "\" failed\n";
      std::cout << "actual: \"" << answer << "\"\n";
      number_of_failed_cases++;
    }
    free(answer);
  }
  auto end = std::chrono::high_resolution_clock::now();

  if (!number_of_failed_cases) {
    std::cout << color("No errors detected", "Green") << " in "
              << color(testName, "Yellow") << ". (finished in "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end -
                                                                      start)
                         .count() *
                     1e-3
              << " \u00b5s)" << '\n';
  } else {
    std::cout << number_of_failed_cases << " error/s detected in "
              << color(testName, "Cyan") << ".\n";
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
  input.emplace_back(
      "435760344379277884633820131779099684238939042431371544682042056116556435"
      "828160653067300006770845128885660665385869518359534463679195446019258869"
      "036799899186047581232658226098666439437335154755530123858374077523694185"
      "67423579728514123284920938751689",
      "144");
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
              "0",
              "2025",
              "6274948959061601538727009897619035453040722211011750243421405608"
              "0784126759255134041691200975001698559535135815565210643772962769"
              "8041442267732771412991854827908516975027845582079672789762622847"
              "9633783560586716341196273708995480906033753028615180243216"};

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
       "8.3066238629180748525842627449074920102322142489556557794321883690"},
      {"190.04963774880799438801", "1.69"}};

  expected = {
      "1",
      "271.8688",
      "30.808499595445775",
      "9.86960440052517106225",
      "0",
      "0.0001",
      "2.25",
      "39.0625",
      "15.625",
      "1938599643512778339818136383900441.479684605423217576299172682002",
      "1."
      "99999999999999999999999999999999999999999999999999999999999999999999999"
      "9"
      "999999999999999999999999999999999999999999999999999999842030259930685943"
      "946527552197663135501198658042590050399725696788570446529764385776702628"
      "001053596055885623266837831449626896",
      "68."
      "999999999999999999999999999999999999999999999999999999999999999375590528"
      "957351438501754916613540326965506490089655688298880161",
      "321.1838877954855105157369"};

  number_of_failed_cases +=
      test_add_mul_sub(multiply, input, expected, functionName, testName);

  functionName = "divide_whole_with_remainder";
  testName = "divide_whole_with_remainder_unit_tests";

  input = {
      {"48", "12"},
      {"108", "18"},
      {"0", "918273"},
      {"24", "13"},
      {"127386", "1928"},
      {"987654321", "123456789"},
      {"2136489764859862341743187349123498", "129387"},
      {"69420", "69421"},
      {"9999999999999999999999999999999999999999",
       "1111111111111111111111111111111111111111"},
      {"4235", "117"},
      {"16758643444472241735565049220950822212345760579123351679767884655871948"
       "59003855646385252010434012887776046783",
       "891702384704657816982436876498261984376893271468926489126897126489"},
      {"2599238273685882301953116803370344458240000000000",
       "37442210799278051022084655767363072000000000"}};

  std::vector<std::pair<std::string, std::string>> expected_div = {
      {"4", "0"},
      {"6", "0"},
      {"0", "0"},
      {"1", "11"},
      {"66", "138"},
      {"8", "9"},
      {"16512398964809929449969373655", "24013"},
      {"0", "69420"},
      {"9", "0"},
      {"36", "23"},
      {"1879398746928651426938692658172648369836247", "0"},
      {"69420", "0"}};

  number_of_failed_cases += test_div(divide_whole_with_remainder, input,
                                     expected_div, functionName, testName);

  functionName = "remove_zeroes";
  testName = "remove_zeroes_unit_tests";
  std::vector<std::string> input_rlz = {
      "001", "1", "0000", "000000.0000000", "-1.0", "-1", "00.32300"};
  expected = {"1", "1", "0", "0", "-1", "-1", "0.323"};

  number_of_failed_cases +=
      test_rlz(remove_zeroes, input_rlz, expected, functionName, testName);

  functionName = "divide";
  testName = "divide_unit_tests";
  input = {{"123", "456"},
           {"2619.995643649944960380551432833049", "1307674368000"},
           {"7482.9695578286078013428929473144712489", "355687428096000"},
           {"1", "3628800"}};
  expected = {"0.26973684210526315789", "0.00000000200355356636",
              "0.00000000002103804904", "0.00000027557319223985"};

  number_of_failed_cases +=
      test_mdiv(divide, input, expected, functionName, testName);

  functionName = "subtract";
  testName = "subtract_unit_tests";
  input = {{"12", "13"}};
  expected = {"-1"};

  number_of_failed_cases +=
      test_add_mul_sub(subtract, input, expected, functionName, testName);

  if (number_of_failed_cases)
    throw std::runtime_error(std::to_string(number_of_failed_cases) +
                             " test/s failed.");

  functionName = "add";
  testName = "addp_unit_tests";
  input = {{"7.41280987770482352328", "3.347589486979800345266962788384"}};
  expected = {"10.760399364684623868546962788384"};

  number_of_failed_cases +=
      test_add_mul_sub(addp, input, expected, functionName, testName);

  if (number_of_failed_cases)
    throw std::runtime_error(std::to_string(number_of_failed_cases) +
                             " test/s failed.");

  std::cout << "\n\n" << std::flush;

  input.clear();
  expected.clear();

  std::cout << "Running " << color("rigourous tests ... ", "Red")
            << "\nNote: Any tests that fail will be explicitly mentioned.\n\n";
  std::cout << "Running 10,000 tests for " << color("add_whole.asm", "Red")
            << ".\n";

  std::string currentDir = get_current_directory();
  std::replace(currentDir.begin(), currentDir.end(), '\\', '/');
  if (currentDir.find("build") != std::string::npos)
    currentDir = currentDir.substr(0, currentDir.find("build"));
  if (currentDir.back() != '/')
    currentDir.push_back('/');

  std::ifstream expectedFile(
      currentDir +
      "src/tests/basic_math_operations_tests/add_whole/expected.txt");
  std::ifstream inputFile(
      currentDir + "src/tests/basic_math_operations_tests/add_whole/input.txt");

  bool failed_tests = false;
  double time = 0;

  if (!expectedFile || !inputFile) {
    std::cout << "Couldn't open test files!\n";
    std::cout << currentDir << "\n";
    return 0;
  }

  size_t i = 0;

  for (i = 0; i < 10000; i++) {
    // If time exceeds 10 seconds, stop the test.
    if (time > 1e7)
      break;

    std::string firstInput;
    std::string secondInput;
    std::string Expected;

    inputFile >> firstInput;
    inputFile >> secondInput;
    expectedFile >> Expected;

    char *res =
        (char *)calloc(firstInput.length() + secondInput.length() + 1, 1);
    auto start = std::chrono::high_resolution_clock::now();
    add_whole(firstInput.c_str(), secondInput.c_str(), res);
    auto end = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count() *
            1e-3;
    if (std::string(res) != Expected) {
      std::cout << color("Error: add_whole(", "Red") << "\"" << firstInput
                << "\", \"" << secondInput << "\"" << color(") failed.", "Red")
                << "\n";
      std::cout << color("Expected: ", "Red") << Expected << '\n';
      std::cout << color("Actual  : ", "Red") << res << '\n';
      free(res);
      failed_tests = true;
      throw std::runtime_error("add_whole.asm failed a test.");
    }
    free(res);
  }

  expectedFile.close();
  inputFile.close();

  if (!failed_tests) {
    std::cout << color(std::to_string(i) + " tests for ", "Green")
              << color("add_whole.asm", "Red") << color(" passed in ", "Green")
              << time << color(" \u00b5s!\n", "Magenta");
  }

  std::cout << "\n";
  std::cout << "Running 10,000 tests for " << color("subtract_whole.asm", "Red")
            << ".\n";

  time = 0;
  expectedFile.open(
      currentDir +
      "src/tests/basic_math_operations_tests/subtract_whole/expected.txt");
  inputFile.open(
      currentDir +
      "src/tests/basic_math_operations_tests/subtract_whole/input.txt");

  if (!expectedFile || !inputFile) {
    std::cout << "Couldn't open test files!\n";
    std::cout << currentDir << "\n";
    return 0;
  }

  for (i = 0; i < 10000; i++) {
    if (time > 1e7)
      break;

    std::string firstInput, secondInput, Expected;
    inputFile >> firstInput >> secondInput;
    expectedFile >> Expected;

    char *res =
        (char *)calloc(firstInput.length() + secondInput.length() + 2, 1);
    auto start = std::chrono::high_resolution_clock::now();
    subtract_whole(firstInput.c_str(), secondInput.c_str(), res);
    auto end = std::chrono::high_resolution_clock::now();
    remove_zeroes(res);
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count() *
            1e-3;
    if (std::string(res) != Expected) {
      std::cout << color("Error: subtract_whole(", "Red") << "\"" << firstInput
                << "\", \"" << secondInput << "\"" << color(") failed.", "Red")
                << "\n";
      std::cout << color("Expected: ", "Red") << Expected << '\n';
      std::cout << color("Actual  : ", "Red") << res << '\n';
      free(res);
      failed_tests = true;
      throw std::runtime_error("subtract_whole.asm failed a test.");
    }

    free(res);
  }

  expectedFile.close();
  inputFile.close();

  if (!failed_tests) {
    std::cout << color(std::to_string(i) + " tests for ", "Green")
              << color("subtract_whole.asm", "Red")
              << color(" passed in ", "Green") << time
              << color(" \u00b5s!\n", "Magenta");
  }

  std::cout << "\n";
  std::cout << "Running 10,000 tests for " << color("multiply_whole.asm", "Red")
            << ".\n";

  time = 0;
  expectedFile.open(
      currentDir +
      "src/tests/basic_math_operations_tests/multiply_whole/expected.txt");
  inputFile.open(
      currentDir +
      "src/tests/basic_math_operations_tests/multiply_whole/input.txt");

  if (!expectedFile || !inputFile) {
    std::cout << "Couldn't open test files!\n";
    std::cout << currentDir << "\n";
    return 0;
  }

  for (i = 0; i < 10000; i++) {
    if (time > 1e7)
      break;

    std::string firstInput, secondInput, Expected;
    inputFile >> firstInput >> secondInput;
    expectedFile >> Expected;

    char *res =
        (char *)calloc(firstInput.length() + secondInput.length() + 2, 1);
    auto start = std::chrono::high_resolution_clock::now();
    multiply_whole(firstInput.c_str(), secondInput.c_str(), res);
    auto end = std::chrono::high_resolution_clock::now();
    remove_zeroes(res);
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count() *
            1e-3;
    if (std::string(res) != Expected) {
      std::cout << color("Error: multiply_whole(", "Red") << "\"" << firstInput
                << "\", \"" << secondInput << "\"" << color(") failed.", "Red")
                << "\n";
      std::cout << color("Expected: ", "Red") << Expected << '\n';
      std::cout << color("Actual  : ", "Red") << res << '\n';
      free(res);
      failed_tests = true;
      throw std::runtime_error("multiply_whole.asm failed a test.");
    }

    free(res);
  }

  expectedFile.close();
  inputFile.close();

  if (!failed_tests) {
    std::cout << color(std::to_string(i) + " tests for ", "Green")
              << color("multiply_whole.asm", "Red")
              << color(" passed in ", "Green") << time
              << color(" \u00b5s!\n", "Magenta");
  }

  std::cout << "\n";
  std::cout << "Running 10,000 tests for "
            << color("divide_whole_with_remainder.asm", "Red") << ".\n";

  time = 0;
  expectedFile.open(currentDir + "src/tests/basic_math_operations_tests/"
                                 "divide_whole_with_remainder/expected.txt");
  inputFile.open(currentDir + "src/tests/basic_math_operations_tests/"
                              "divide_whole_with_remainder/input.txt");

  if (!expectedFile || !inputFile) {
    std::cout << "Couldn't open test files!\n";
    std::cout << currentDir << "\n";
    return 0;
  }

  for (i = 0; i < 10000; i++) {
    if (time > 1e7)
      break;

    std::string firstInput, secondInput, firstExpected, secondExpected;
    inputFile >> firstInput >> secondInput;
    expectedFile >> firstExpected >> secondExpected;

    char *quotient =
        (char *)calloc(firstInput.length() + secondInput.length() + 2, 1);
    char *remainder =
        (char *)calloc(firstInput.length() + secondInput.length() + 2, 1);
    auto start = std::chrono::high_resolution_clock::now();
    divide_whole_with_remainder(firstInput.c_str(), secondInput.c_str(),
                                quotient, remainder);
    auto end = std::chrono::high_resolution_clock::now();
    remove_zeroes(quotient);
    remove_zeroes(remainder);
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                .count() *
            1e-3;
    if (std::string(quotient) != firstExpected ||
        std::string(remainder) != secondExpected) {
      std::cout << color("Error: divide_whole_with_remainder(", "Red") << "\""
                << firstInput << "\", \"" << secondInput << "\""
                << color(") failed.", "Red") << "\n";
      std::cout << color("Expected: ", "Red") << firstExpected << ", "
                << secondExpected << "\n";
      std::cout << color("Actual  : ", "Red") << quotient << ", " << remainder
                << "\n";
      free(quotient);
      free(remainder);
      failed_tests = true;
      throw std::runtime_error(
          "divide_whole_with_remainder.asm failed a test.");
    }

    free(quotient);
    free(remainder);
  }

  expectedFile.close();
  inputFile.close();

  if (!failed_tests) {
    std::cout << color(std::to_string(i) + " tests for ", "Green")
              << color("divide_whole_with_remainder.asm", "Red")
              << color(" passed in ", "Green") << time
              << color(" \u00b5s!\n", "Magenta");
  }
}