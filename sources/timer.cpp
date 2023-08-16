#include "../headers/timer.hpp"

int64_t Timer::getNanoseconds() const {
  return std::chrono::duration_cast<nanosecond_t>(clock_t::now() - start)
      .count();
}

int64_t Timer::getMicroseconds() const {
  return std::chrono::duration_cast<microsecond_t>(clock_t::now() - start)
      .count();
}

int64_t Timer::getMilliseconds() const {
  return std::chrono::duration_cast<millisecond_t>(clock_t::now() - start)
      .count();
}

int64_t Timer::getSecond() const {
  return std::chrono::duration_cast<second_t>(clock_t::now() - start).count();
}

int64_t Timer::getMinutes() const {
  return std::chrono::duration_cast<minute_t>(clock_t::now() - start).count();
}

int64_t Timer::getHours() const {
  return std::chrono::duration_cast<hour_t>(clock_t::now() - start).count();
}

void Timer::reset() { start = clock_t::now(); }