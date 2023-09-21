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

  void operator()() const { mFunc(); }
};

#endif  // _BENCHMARK_HPP_