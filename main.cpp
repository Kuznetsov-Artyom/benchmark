#include <iostream>
#include <vector>

#include "benchmark.hpp"
#include "timer.hpp"

void testEmplaceBack() {
  std::vector<int> vec;
  for (int j = 0; j < 1'000'000; ++j) vec.emplace_back(j + 1);
}

void testPushBack() {
  std::vector<int> vec;
  for (int j = 0; j < 1'000'000; ++j) vec.push_back(j + 1);
}

void testOperatorInd() {
  std::vector<int> vec(1'000'000);
  for (int j = 0; j < 1'000'000; ++j) vec[j] = j + 1;
}

template <typename Func, typename... Args>
auto wrapper(Func&& func, Args&&... args) {
  return func(std::forward<Args>(args)...);
}

int addition(int valueOne, int valueTwo) { return valueOne + valueTwo; }

void printHello() { std::cout << "Hello World!\n"; }

int main() {
  std::cout << wrapper(addition, 100, 200) << '\n';
  wrapper(printHello);

  BMK_CREATE(benchAddition, addition, 100, 200);
  int test = BMK_START(benchAddition, 10);

  if (test == BMK_EXIT_SUCCESS) {
    std::cout << BMK_GET_INFO(benchAddition) << '\n';
  }

  /*BMK_CREATE(testPush, testPushBack);
  BMK_CREATE(testEmplace, testEmplaceBack);
  BMK_CREATE(testInd, testOperatorInd);
  size_t countTests = 1;

  BMK_START(testPush, countTests) << '\n';
  BMK_START(testEmplace, countTests) << '\n';
  BMK_START(testInd, countTests) << '\n';

  BMK_CREATE(bench, printHello);
  BMK_START(bench, 5) << '\n';*/

  return 0;
}