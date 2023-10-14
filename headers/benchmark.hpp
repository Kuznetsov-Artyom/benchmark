#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

#include <functional>

#include "timer.hpp"

#define BMK_CREATE(varName, func, ...) bmk::Benchmark varName(func, __VA_ARGS__)
#define BMK_START(varName, period, layout, countTests) \
  varName.operator()<period>(layout, countTests);
#define BMK_GET_INFO(varName) varName.getResult()

namespace bmk {
enum ExitCode { SUCCESS = 0, FAILURE = -1 };
enum ResultCode { NO_STARTED = -1, EXE_ERROR = -2, LAYOUT_ERROR = -3 };
enum Layout { AVERAGE, BEST, DEL_TAIL };

template <typename Func, typename... Args>
class Benchmark {
 private:
  std::function<void()> mFunc;
  int64_t mLastResult;

 public:
  Benchmark(Func&& fn, Args... args)
      : mFunc{std::bind(std::forward<Func>(fn), args...)},
        mLastResult{ResultCode::NO_STARTED} {}
  Benchmark(const Benchmark&) = delete;
  Benchmark(Benchmark&&) = delete;

  int64_t getResult();

  template <typename Period>
  int operator()(int layout, const size_t& countTests);

  Benchmark& operator=(const Benchmark&) = delete;
  Benchmark& operator=(Benchmark&&) = delete;
};

template <typename Func, typename... Args>
inline int64_t Benchmark<Func, Args...>::getResult() {
  return mLastResult;
}

template <typename Func, typename... Args>
template <typename Period>
inline int Benchmark<Func, Args...>::operator()(int layout,
                                                const size_t& countTests) {
  int64_t total = 0;
  int64_t curRes = -1;
  int64_t minRes = INT64_MAX;
  int64_t maxRes = INT64_MIN;

  try {
    for (size_t i = 0; i < countTests; ++i) {
      auto func = mFunc;
      TIMER_START(timer, Period);
      func();
      curRes = TIMER_GET(timer);

      if (curRes < minRes) minRes = curRes;
      if (curRes > maxRes) maxRes = curRes;

      total += curRes;
    }
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << '\n';
    mLastResult = ResultCode::EXE_ERROR;
    return ExitCode::FAILURE;
  }

  switch (layout) {
    case Layout::AVERAGE:
      mLastResult = total / countTests;
      break;
    case Layout::BEST:
      mLastResult = minRes;
      break;
    case Layout::DEL_TAIL:
      mLastResult = (total - maxRes) / (countTests - 1);
      break;
    default:
      mLastResult = ResultCode::LAYOUT_ERROR;
      return ExitCode::FAILURE;
      break;
  }
  return ExitCode::SUCCESS;
}
}  // namespace bmk

#endif  // _BENCHMARK_HPP_