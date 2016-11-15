#include "CFile.hpp"
#include "Subject.hpp"
#include "TimeSignal.hpp"
#include "convolution-filters.hpp"
#include <thread>

#include <cstdio>

using namespace std::chrono_literals;

struct FilePrinter : public Observer {
  CFile tgtFile;
  FilePrinter(CFile &&f) : tgtFile(std::move(f)) {}
  void update(Subject *s) {
    auto sig = dynamic_cast<signal::TimeSignal *>(s);
    auto val = sig->get();
    auto time = val.first.time_since_epoch().count();
    tgtFile.write(std::string{std::to_string(time) + '\t' +
                              std::to_string(val.second) + '\n'});
  }
};

int main() {
  FilePrinter unfilteredPrinter(CFile{"unfiltered.out", "w"});
  FilePrinter filteredPrinter(CFile{"filtered.out", "w"});
  FilePrinter origPrinter(CFile{"orig.out", "w"});

  auto proxHeart = std::make_shared<signal::HeartBeatProxy>();
  signal::HeartBeat heart;
  signal::SineWave sineSource;
  signal::Noisifier noiseSource;
  filter::SlidingAverage<7> box;

  heart.attach_observer(proxHeart.get());
  heart.attach_observer(&sineSource);
  sineSource.attach_observer(&noiseSource);
  noiseSource.attach_observer(&box);

  sineSource.attach_observer(&origPrinter);
  noiseSource.attach_observer(&unfilteredPrinter);
  box.attach_observer(&filteredPrinter);

  auto pacemaker = std::thread(std::move(heart), proxHeart);
  auto startTime = signal::clock::now();
  while (true) {
    if (signal::clock::now() - startTime >= 3s) {
      proxHeart->kill();
      break;
    } else {
      std::this_thread::yield();
    }
  };
  pacemaker.join();

  return 0;
}
