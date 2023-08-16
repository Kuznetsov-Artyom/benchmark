#include <iostream>
#include <vector>

#include "headers/timer.hpp"

void testEmplaceBack() {
  Timer timer;

  for (int i = 0; i < 200; ++i) {
    std::vector<int> vec;

    for (int j = 0; j < 1'000'000; ++j) vec.emplace_back(j + 1);
  }

  std::cout << timer.getNanoseconds() << '\n';
}

void testPushBack() {
  Timer timer;

  for (int i = 0; i < 500; ++i) {
    std::vector<int> vec;

    for (int j = 0; j < 1'000'000; ++j) vec.push_back(j + 1);
  }

  std::cout << timer.getNanoseconds() << '\n';
}

void testOperatorInd() {
  Timer timer;

  for (int i = 0; i < 500; ++i) {
    std::vector<int> vec(1'000'000);

    for (int j = 0; j < 1'000'000; ++j) vec[j] = j + 1;

    vec.clear();
  }

  std::cout << timer.getNanoseconds() << '\n';
}

int main() {
  testEmplaceBack();
  testPushBack();
  testOperatorInd();

  return 0;
}