#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <map>
#include <vector>

template <typename InfoType>
class Observer;

template <typename InfoType>
class Subject {
    std::map<int, Observer<InfoType> *> straightObservers;  // Used for rook and queen
    std::map<int, Observer<InfoType> *> diagonalObservers;  // Used for bishop and queen
    std::vector<Observer<InfoType> *> knightObservers;      // Used for knights
    InfoType info;                                          // Info sent to the observer

   protected:
    void notifyStraightObservers(int direction = 0);  // If direction = 0, notify all straight observer. Else, notify the specified observer
    void notifyDiagonalObservers(int direction = 0);  // If direction = 0, notify all diagonal observer. Else, notify the specified observer
    void notifyKnightObservers();                     // Notify all knight observers
    void setInfo(InfoType info);                      // Sets the info sent to the observer
    InfoType getInfo() const;                         // Gets the info sent to the observer

   public:
    void attachStraight(int direction, Observer<InfoType> *o);  // Adds the observer to the list of straight observers with the direction
    void attachDiagonal(int direction, Observer<InfoType> *o);  // Adds the observer to the list of diagonal observers with the direction
    void attachKnight(Observer<InfoType> *o);                   // Adds the observer to the list of knight observers
};

#endif