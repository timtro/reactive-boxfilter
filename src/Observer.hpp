#ifndef SRC_OBSERVER_HPP_
#define SRC_OBSERVER_HPP_

class Subject;

/**
 * A faithful inplementation of the Gang of Four _observer_ pattern.
 * See Subject.hpp for the subject half of the pattern.
 */
class Observer {
public:
  virtual ~Observer() = default;
  virtual void update(Subject *) = 0;

protected:
  Observer() = default;
};

#endif // SRC_OBSERVER_HPP_
