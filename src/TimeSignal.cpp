#include "TimeSignal.hpp"
#include <cmath>
#include <random>
#include <thread>

namespace signal {

HeartBeat::HeartBeat(HeartBeat &&orig) {
  observers = orig.observers;
  orig.observers.clear();
}
void HeartBeat::operator()(std::shared_ptr<HeartBeatProxy> ctrl) {
  while (true) {
    if (ctrl->is_expired()) {
      return;
    }
    lastTick = clock::now();
    notify();
    std::this_thread::sleep_for(10ms);
  }
}
decltype(HeartBeat::lastTick) HeartBeat::get() { return lastTick; }

void HeartBeatProxy::update(Subject *s) {
  auto sub = static_cast<HeartBeat *>(s);
  lastBeat = sub->get();
}
clock_point HeartBeatProxy::get() { return lastBeat; }
bool HeartBeatProxy::is_expired() { return this->isExpired; }
void HeartBeatProxy::kill() { isExpired = true; }

void SineWave::update(Subject *s) {
  auto heart = dynamic_cast<HeartBeat *>(s);
  value.first = heart->get();
  value.second = std::sin(
      duration_cast<milliseconds>(value.first.time_since_epoch()).count() /
      60.f);
  notify();
}

Noisifier::Noisifier() {
  std::random_device r;
  std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937 rndEngine(seed);
}

void Noisifier::update(Subject *s) {
  double rndm = dist(rndEngine);
  auto sig = dynamic_cast<TimeSignal *>(s);
  value = sig->get();
  value.second += rndm;
  notify();
}
}
