#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

#include <functional>

#include "timer.hpp"


// template <typename Func>
// class Benchmark {
//  private:
//   Func func; // function under test

//  public:
//   Benchmark(Func f, const size_t& countTests = 1) : func{f} {}

//   int64_t operator()(const size_t& countTests = 1) {
//     Timer timer;

//     for (size_t numTest = 0; numTest < countTests; ++numTest) {
//       func();
//     }

//     return timer.getNanoseconds();
//   }
//};

#endif  // _BENCHMARK_HPP_