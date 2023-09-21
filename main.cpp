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
  /*size_t countTests = 300;

  TIMER_START(timer, tmr::millisecond_t);

  for (size_t i = 0; i < countTests; ++i) testPushBack();

  std::cout << TIMER_GET(timer) << '\n';*/

  std::cout << wrapper(addition, 100, 200) << '\n';
  wrapper(printHello);

  Benchmark benchmark(addition, 100, 200);

  benchmark();
  benchmark();

  Benchmark benchmark2(printHello);

  benchmark2();
  benchmark2();

  return 0;
}