
#ifndef INTEGRAL_CONCURRENTLY_TIME_MEASURE_H
#define INTEGRAL_CONCURRENTLY_TIME_MEASURE_H

#include <iostream>
#include <chrono>
#include <atomic>

inline std::chrono::steady_clock::time_point get_current_time_fenced();

template<class D>
inline long long to_us(const D& d)
{ return std::chrono::duration_cast<std::chrono::microseconds>(d).count(); }

#endif //INTEGRAL_CONCURRENTLY_TIME_MEASURE_H
