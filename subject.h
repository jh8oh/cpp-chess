#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "observer.h"

class Subject {
    Observer *observer;

   public:
    Subject();
    ~Subject();
    void setObserver(Observer *o);
    void notifyObserver(Mate mateInfo);
};

#endif