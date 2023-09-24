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

static int64_t printVector(std::vector<int> elems) {
  std::cout << elems << '\n';
  return 0;
}

int main() {
  std::vector<int> elems{1, 2, 3, 4, 5};

  BMK_CREATE(testPrintVec, printVector, elems);
  int codePrintVec = BMK_START(testPrintVec, 3);

  if (codePrintVec == 0) {
    std::cout << BMK_GET_INFO(testPrintVec) << '\n';
  }

  BMK_CREATE(testPush, testPushBack);
  BMK_CREATE(testEmplace, testEmplaceBack);
  BMK_CREATE(testInd, testOperatorInd);
  size_t countTests = 100;

  int codePush = BMK_START(testPush, countTests);
  int codeEmpl = BMK_START(testEmplace, countTests);
  int codeInd = BMK_START(testInd, countTests);

  if (codePush == 0 && codeEmpl == 0 && codeInd == 0) {
    std::cout << "push:\t" << BMK_GET_INFO(testPush) << '\n';
    std::cout << "empl:\t" << BMK_GET_INFO(testEmplace) << '\n';
    std::cout << "ind:\t" << BMK_GET_INFO(testInd) << '\n';
  }

  return 0;
}