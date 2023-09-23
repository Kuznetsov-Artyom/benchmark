#include <iostream>
#include <vector>

#include "benchmark.hpp"
#include "timer.hpp"

static void testEmplaceBack() {
  std::vector<int> vec;
  for (int j = 0; j < 1'000'000; ++j) vec.emplace_back(j + 1);
}

static void testPushBack() {
  std::vector<int> vec;
  for (int j = 0; j < 1'000'000; ++j) vec.push_back(j + 1);
}

static void testOperatorInd() {
  std::vector<int> vec(1'000'000);
  for (int j = 0; j < 1'000'000; ++j) vec[j] = j + 1;
}

int main() {
  BMK_CREATE(testPush, testPushBack);
  BMK_CREATE(testEmplace, testEmplaceBack);
  BMK_CREATE(testInd, testOperatorInd);
  size_t countTests = 100;

  int codePush = BMK_START(testPush, countTests);
  int codeEmpl = BMK_START(testEmplace, countTests);
  int codeInd = BMK_START(testInd, countTests);

  if (codePush == 0 && codeEmpl == 0 && codeInd == 0) {
    std::cout << "push: " << BMK_GET_INFO(testPush) << '\n';
    std::cout << "empl: " << BMK_GET_INFO(testEmplace) << '\n';
    std::cout << "ind: " << BMK_GET_INFO(testInd) << '\n';
  }

  return 0;
}