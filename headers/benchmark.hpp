#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

#include <functional>

#include "timer.hpp"

template <typename Func, typename... Args>
class Benchmark {
 private:
  std::function<void()> mFunc;

 public:
  Benchmark(Func&& fn, Args&&... args)
      : mFunc{std::bind(std::forward<Func>(fn), std::forward<Args>(args)...)} {}

  int64_t operator()(const size_t& countTests) const {
    int64_t total = 0;

    for (size_t i = 0; i < countTests; ++i) {
      TIMER_START(timer, tmr::millisecond_t);
      mFunc();
      total += TIMER_GET(timer);
    }

    return total / countTests;
  }
};

#endif  // _BENCHMARK_HPP_