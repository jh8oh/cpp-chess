#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "mate.h"

class Observer {
   public:
    virtual void notify(Mate mateInfo) = 0;
    virtual ~Observer();
};

#endif