#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <map>
#include <vector>

template <typename InfoType>
class Observer;

template <typename InfoType>
class Subject {
    static std::map<int, bool> isStraightObserver = {{8, true}, {4, true}, {2, true}, {1, true}, {10, false}, {9, false}, {6, false}, {5, false}};  // Maps whether the observer is straight or not (Used for O(1) time for lookup)

    std::map<int, Observer<InfoType> *> neighbourObservers;  // Used for bishops, rooks, queens, pawns, and kings
    std::vector<Observer<InfoType> *> knightObservers;       // Used for knights
    InfoType info;                                           // Info sent to the observer

   protected:
    void notifyStraightObservers(int direction = 0);  // If direction = 0, notify all straight observer. Else, notify the specified observer
    void notifyDiagonalObservers(int direction = 0);  // If direction = 0, notify all diagonal observer. Else, notify the specified observer
    void notifyKnightObservers();                     // Notify all knight observers
    void setInfo(InfoType info);                      // Sets the info sent to the observer
    InfoType getInfo() const;                         // Gets the info sent to the observer

   public:
    void attachNeighbour(int direction, Observer<InfoType> *o);  // Adds the observer to the list of neighbouring observers with the direction
    void attachKnight(Observer<InfoType> *o);                    // Adds the observer to the list of knight observers
};

#endif