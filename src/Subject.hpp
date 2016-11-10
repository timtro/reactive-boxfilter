#ifndef SRC_SUBJECT_HPP_
#define SRC_SUBJECT_HPP_

#include "Observer.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>

/**
 * A faithful inplementation of the Gang of Four _observer_ pattern.
 * See Observer.hpp for the observer half of the pattern.
 */
class Subject {
public:
  virtual void attach_observer(Observer *);
  virtual void detach_observer(Observer *);
  virtual void notify();
  Subject() = default;

protected:
  virtual ~Subject() = default;
  std::vector<Observer *> observers{};
};

class AttemptToAttachAlreadyAttachedObserver : public std::exception {
  virtual const char *what() const noexcept override {
    return "An attempt has been made to subscribe a subject more than once to "
           "the same observer list.";
  }
};

#endif // SRC_SUBJECT_HPP_
