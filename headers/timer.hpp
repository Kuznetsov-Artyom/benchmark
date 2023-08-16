#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <chrono>

class Timer {
 private:
  using clock_t = std::chrono::high_resolution_clock;
  using nanosecond_t = std::chrono::nanoseconds;
  using microsecond_t = std::chrono::microseconds;
  using millisecond_t = std::chrono::milliseconds;
  using second_t = std::chrono::seconds;
  using minute_t = std::chrono::minutes;
  using hour_t = std::chrono::hours;

  std::chrono::time_point<clock_t> start;

 public:
  Timer() : start{clock_t::now()} {}

  int64_t getNanoseconds() const;
  int64_t getMicroseconds() const;
  int64_t getMilliseconds() const;
  int64_t getSecond() const;
  int64_t getMinutes() const;
  int64_t getHours() const;

  void reset();
};

#endif  // _TIMER_HPP_