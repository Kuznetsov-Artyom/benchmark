#include <iostream>
#include <vector>

#include "headers/benchmark.hpp"

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

int main() {
  size_t countTests = 300;

  timer::Timer<timer::millisecond_t> timer;

  for (size_t i = 0; i < countTests; ++i) testPushBack();

  std::cout << timer() << '\n';

  return 0;
}