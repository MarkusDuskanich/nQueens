#ifndef NQUEENS_DIAGONAL_H
#define NQUEENS_DIAGONAL_H

#include "../Queen/Queen.h"
#include <stdexcept>
#include <iostream>

class Diagonal{
private:
    int* diagonals;
    int arrayLength;
    int validDiagonals;
    int squareDimension;

    int negDiagonalIndexOf(Queen &q) const;
    int posDiagonalIndexOf(Queen &q) const;
    void throwErrorIfIndexOutOfRange(int index);
    bool indexOutOfRange(int index) const;
    int& at(int index);



public:
    explicit Diagonal(int squareDimension);

    void add(Queen &q);
    void remove(Queen &q);

    void addQueenAndUpdateValidDiagonals(int index);
    void removeQueenAndUpdateValidDiagonals(int index);
    bool isValidConfiguration() const;
    void reset();
    int conflicts(Queen &q);
    void print();

    ~Diagonal();
};


#endif //NQUEENS_DIAGONAL_H
