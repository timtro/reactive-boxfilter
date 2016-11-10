#ifndef SRC_CONVOLUTION_FILTERS_HPP_
#define SRC_CONVOLUTION_FILTERS_HPP_

#include "Observer.hpp"
#include "Subject.hpp"
#include "TimeSignal.hpp"
#include <boost/circular_buffer.hpp>
#include <chrono>
#include <numeric>

namespace filter {

struct SlidingAverage : public signal::TimeSignal,
                        public Observer,
                        public boost::circular_buffer<double> {

  SlidingAverage(unsigned n) : boost::circular_buffer<double>(n) {}

  signal::signal_value get() { return value; }

  virtual void update(Subject *s) {
    auto obs = dynamic_cast<signal::TimeSignal *>(s);
    auto obs_val = obs->get();
    value.first = obs_val.first;
    push_back(obs_val.second);
    value.second = std::accumulate(begin(), end(), 0.) / size();
    notify();
  }
};
}

#endif // SRC_CONVOLUTION_FILTERS_HPP_
