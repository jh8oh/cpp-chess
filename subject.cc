#include "subject.h"

Subject::Subject() {}

Subject::~Subject() {
    delete observer;
}

void Subject::setObserver(Observer *o) {
    observer = o;
}

void Subject::notifyObserver(Mate mateInfo) {
    observer->notify(mateInfo);
}