#include <algorithm>
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

template <typename T, template <typename Elem, typename = std::allocator<Elem>>
                      class Container>
std::ostream& operator<<(std::ostream& out, const Container<T>& cont) {
  auto itBegin = cont.begin();
  auto itEnd = cont.begin() + cont.size() - 1;

  for (; itBegin != itEnd; ++itBegin) out << *itBegin << ' ';
  return out << *itBegin;
}

static void sortPrintVector(std::vector<int> elems) {
  std::cout << elems << '\n';
  std::sort(elems.begin(), elems.end());
  std::cout << elems << '\n';
}

int main() {
  std::vector<int> elems{5, 3, 0, 1, 2, 4};

  BMK_CREATE(testPrintVec, sortPrintVector, elems);
  int codePrintVec = BMK_START(testPrintVec, tmr::millisecond_t, 0, 3);

  if (codePrintVec == 0) {
    std::cout << BMK_GET_INFO(testPrintVec) << '\n';
  }

  BMK_CREATE(testPush, testPushBack);
  BMK_CREATE(testEmplace, testEmplaceBack);
  BMK_CREATE(testInd, testOperatorInd);
  size_t countTests = 100;

  // test (ms)
  int codePush = BMK_START(testPush, tmr::millisecond_t, 0, countTests);
  int codeEmpl = BMK_START(testEmplace, tmr::millisecond_t, 0, countTests);
  int codeInd = BMK_START(testInd, tmr::millisecond_t, 0, countTests);

  if (codePush == 0 && codeEmpl == 0 && codeInd == 0) {
    std::cout << "push:\t" << BMK_GET_INFO(testPush) << '\n';
    std::cout << "empl:\t" << BMK_GET_INFO(testEmplace) << '\n';
    std::cout << "ind:\t" << BMK_GET_INFO(testInd) << '\n';
  }

  std::cout << '\n';

  // test (ns)
  codePush = BMK_START(testPush, tmr::nanosecond_t, 1, countTests);
  codeEmpl = BMK_START(testEmplace, tmr::nanosecond_t, 1, countTests);
  codeInd = BMK_START(testInd, tmr::nanosecond_t, 1, countTests);

  if (codePush == 0 && codeEmpl == 0 && codeInd == 0) {
    std::cout << "push:\t" << BMK_GET_INFO(testPush) << '\n';
    std::cout << "empl:\t" << BMK_GET_INFO(testEmplace) << '\n';
    std::cout << "ind:\t" << BMK_GET_INFO(testInd) << '\n';
  }

  return 0;
}