#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

#include <functional>

#include "timer.hpp"

#define BMK_CREATE(varName, func, ...) bmk::Benchmark varName(func, __VA_ARGS__)
#define BMK_START(varName, countTests) varName(countTests)
#define BMK_GET_INFO(varName) varName.getResult()

namespace bmk {
enum ExitCode { SUCCESS = 0, FAILURE = -1 };
enum ResultCode { NO_STARTED = -1, ERROR = -2 };

template <typename Func, typename... Args>
class Benchmark {
 private:
  std::function<void()> mFunc;
  int64_t mLastResult;

 public:
  Benchmark(Func&& fn, Args&&... args)
      : mFunc{std::bind(std::forward<Func>(fn), std::forward<Args>(args)...)},
        mLastResult{ResultCode::NO_STARTED} {}
  Benchmark(const Benchmark&) = delete;
  Benchmark(Benchmark&&) = delete;

  int64_t getResult();

  int operator()(const size_t& countTests);

  Benchmark& operator=(const Benchmark&) = delete;
  Benchmark& operator=(Benchmark&&) = delete;
};

template <typename Func, typename... Args>
inline int64_t Benchmark<Func, Args...>::getResult() {
  return mLastResult;
}

template <typename Func, typename... Args>
inline int Benchmark<Func, Args...>::operator()(const size_t& countTests) {
  int64_t total = 0;
  try {
    for (size_t i = 0; i < countTests; ++i) {
      TIMER_START(timer, tmr::millisecond_t);
      mFunc();
      total += TIMER_GET(timer);
    }
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << '\n';
    mLastResult = ResultCode::ERROR;
    return ExitCode::FAILURE;
  }
  mLastResult = total / countTests;
  return ExitCode::SUCCESS;
}
}  // namespace bmk

#endif  // _BENCHMARK_HPP_