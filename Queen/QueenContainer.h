#ifndef NQUEENS_QUEENCONTAINER_H
#define NQUEENS_QUEENCONTAINER_H

#include "Queen.h"
#include "../Coordinates/CoordinateServiceI.h"
#include <stdexcept>

class QueenContainer{
private:
    Queen *queens;
    int length;

    bool indexOutOfRange(int index) const;
    void throwErrorIfOutOfRange(int index) const;

public:
    explicit QueenContainer(int length);
    QueenContainer(const QueenContainer &origin);

    Queen& at(int index) const;
    int size() const;
    ~QueenContainer();
};


#endif //NQUEENS_QUEENCONTAINER_H
