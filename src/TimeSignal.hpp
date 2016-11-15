#ifndef SRC_TIMESIGNAL_HPP_
#define SRC_TIMESIGNAL_HPP_

#include "Subject.hpp"
#include <chrono>
#include <memory>

namespace signal {

using namespace std::chrono_literals;
using clock = std::chrono::steady_clock;
using clock_point = std::chrono::time_point<std::chrono::steady_clock>;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::duration;

using signal_value = std::pair<clock_point, double>;

struct TimeSignal : public Subject {
  signal_value value;
  virtual signal_value get() { return value; };
};

class HeartBeatProxy;

struct HeartBeat : public Subject {

  clock_point lastTick = clock::now();

  HeartBeat() = default;
  HeartBeat(HeartBeat &&orig);
  HeartBeat(const HeartBeat &) = delete;
  HeartBeat &operator=(HeartBeat &) = delete;

  void operator()(std::shared_ptr<HeartBeatProxy>);
  decltype(lastTick) get();
};

class HeartBeatProxy : public Observer {
  bool isExpired = false;
  clock_point lastBeat;

public:
  void update(Subject *);
  clock_point get();
  bool is_expired();
  void kill();
};

struct SineWave : public TimeSignal, public Observer {
  virtual void update(Subject *);
};

struct Noisifier : public TimeSignal, public Observer {
  std::mt19937 rndEngine;
  std::normal_distribution<> dist{0, .1};

  Noisifier();
  void update(Subject *);
};
}
#endif // SRC_TIMESIGNAL_HPP_
