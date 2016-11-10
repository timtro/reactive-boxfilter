#include "Subject.hpp"

void Subject::attach_observer(Observer *o) {
  if (std::find(observers.begin(), observers.end(), o) == observers.end())
    observers.push_back(o);
  else
    throw AttemptToAttachAlreadyAttachedObserver();
}

void Subject::detach_observer(Observer *o) {
  observers.erase(std::remove(observers.begin(), observers.end(), o),
                  observers.end());
}

void Subject::notify() {
  for (auto &o : observers) {
    o->update(this);
  }
}
