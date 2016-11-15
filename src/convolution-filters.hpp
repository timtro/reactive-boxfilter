#ifndef SRC_CONVOLUTION_FILTERS_HPP_
#define SRC_CONVOLUTION_FILTERS_HPP_

#include "Observer.hpp"
#include "Subject.hpp"
#include "TimeSignal.hpp"
#include <boost/circular_buffer.hpp>
#include <chrono>
#include <numeric>

#include <cstdio>

namespace filter {

template <typename T> T next_closest_odd_int(T k) {
  if (k % 2 == 0)
    return k;
  else
    return k + 1;
}

template <size_t N>
struct SlidingAverage : public signal::TimeSignal, public Observer {

  boost::circular_buffer<decltype(signal::signal_value().first)> time;
  boost::circular_buffer<decltype(signal::signal_value().second)> mag;

  SlidingAverage() {
    auto n = next_closest_odd_int(N);
    time = boost::circular_buffer<decltype(signal::signal_value().first)>(n);
    mag = boost::circular_buffer<decltype(signal::signal_value().second)>(n);
  }

  signal::signal_value get() { return value; }
  virtual void update(Subject *s) {
    auto obsval = dynamic_cast<signal::TimeSignal *>(s)->value;
    time.push_back(obsval.first);
    mag.push_back(obsval.second);
    value.first = time[0] + (*(time.end() - 1) - *time.begin()) / 2;
    value.second = std::accumulate(mag.begin(), mag.end(), 0.) / mag.size();
    notify();
  }
};
}

#endif // SRC_CONVOLUTION_FILTERS_HPP_
