#include "subject.h"

template <typename InfoType>
void Subject<InfoType>::attachStraight(int direction, Observer<InfoType> *o) {
    straightObservers[direction] = o;
}

template <typename InfoType>
void Subject<InfoType>::attachDiagonal(int direction, Observer<InfoType> *o) {
    diagonalObservers[direction] = o;
}

template <typename InfoType>
void Subject<InfoType>::attachKnight(Observer<InfoType> *o) {
    knightObservers.emplace_back(o);
}

template <typename InfoType>
void Subject<InfoType>::notifyStraightObservers(int direction) {
    if (direction == 0) {
        for (auto &ob : straightObservers) {
            (ob.second)->notify(this);
        }
    } else {
        (straightObservers[direction])->notify(this);
    }
}

template <typename InfoType>
void Subject<InfoType>::notifyDiagonalObservers(int direction) {
    if (direction == 0) {
        for (auto &ob : diagonalObservers) {
            (ob.second)->notify(this);
        }
    } else {
        (diagonalObservers[direction])->notify(this);
    }
}

template <typename InfoType>
void Subject<InfoType>::notifyKnightObservers() {
    for (auto &ob : knightObservers) {
        ob->notify(this);
    }
}

template <typename InfoType>
void Subject<InfoType>::setInfo(InfoType info) {
    this->info = info;
}

template <typename InfoType>
InfoType Subject<InfoType>::getInfo() {
    return info;
}