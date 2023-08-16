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
  Benchmark<std::function<void()>> testEmplace(testEmplaceBack);
  Benchmark<std::function<void()>> testPush(testPushBack);
  Benchmark<std::function<void()>> testOperator(testOperatorInd);

    size_t countTests = 300;

  std::cout << "Test emplace_back: " << testEmplace(countTests) << '\n';
  std::cout << "Test push_back: " << testPush(countTests) << '\n';
  std::cout << "Test operator[]: " << testOperator(countTests) << '\n';

  return 0;
}