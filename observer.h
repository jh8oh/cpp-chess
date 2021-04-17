#ifndef _OBSERVER_H_
#define _OBSERVER_H_

template <typename InfoType>
class Subject;

class Square;

template <typename InfoType>
class Observer {
   public:
    virtual ~Observer() = default;  // Destructor

    virtual void notify(Subject<InfoType> &whoFrom) = 0;  // This is called by the subject
};

#endif