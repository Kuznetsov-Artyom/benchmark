#ifndef _BENCHMARK_HPP_
#define _BENCHMARK_HPP_

#include <functional>

#include "timer.hpp"

#define BMK_CREATE(varName, func, ...) bmk::Benchmark varName(func, __VA_ARGS__)
#define BMK_START(varName, period, countTests) \
  varName.operator()<period>(countTests);
#define BMK_GET_INFO(varName) varName.getInfo()
#define BMK_GET_AVG(varName) varName.getInfo().mAvg
#define BMK_GET_BEST(varName) varName.getInfo().mBest
#define BMK_GET_DEL_TAIL(varName) varName.getInfo().mDelTail

namespace bmk {
enum ExitCode { SUCCESS = 0, EXE_ERROR = -1, COUNT_TESTS_IS_ZERO = -2 };
enum ResultCode { NO_STARTED = -1, ERROR = -2 };
enum Layout { AVERAGE, BEST, DEL_TAIL };

struct Info {
  int64_t mAvg = ResultCode::NO_STARTED;
  int64_t mBest = ResultCode::NO_STARTED;
  int64_t mDelTail = ResultCode::NO_STARTED;

  Info() {}
  Info(ResultCode code) : mAvg{code}, mBest{code}, mDelTail{code} {}
  Info(int64_t avg, int64_t best, int64_t delTail)
      : mAvg{avg}, mBest{best}, mDelTail{delTail} {}
};

template <typename Func, typename... Args>
class Benchmark {
 private:
  std::function<void()> mFunc;
  Info mLastResult;

 public:
  Benchmark(Func&& fn, Args... args)
      : mFunc{std::bind(std::forward<Func>(fn), args...)} {}
  Benchmark(const Benchmark&) = delete;
  Benchmark(Benchmark&&) = delete;

  Info getInfo();

  template <typename Period>
  int operator()(const size_t& countTests);

  Benchmark& operator=(const Benchmark&) = delete;
  Benchmark& operator=(Benchmark&&) = delete;
};

template <typename Func, typename... Args>
inline Info Benchmark<Func, Args...>::getInfo() {
  return mLastResult;
}

template <typename Func, typename... Args>
template <typename Period>
inline int Benchmark<Func, Args...>::operator()(const size_t& countTests) {
  if (countTests == 0) {
    mLastResult = Info(ResultCode::ERROR);
    return ExitCode::COUNT_TESTS_IS_ZERO;
  }

  int64_t total = 0;
  int64_t curRes = 0;
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
    mLastResult = Info(ResultCode::ERROR);
    return ExitCode::EXE_ERROR;
  }

  mLastResult.mAvg = total / countTests;
  mLastResult.mBest = minRes;
  mLastResult.mDelTail = (total - maxRes) / (countTests - 1);

  return ExitCode::SUCCESS;
}
}  // namespace bmk

#endif  // _BENCHMARK_HPP_