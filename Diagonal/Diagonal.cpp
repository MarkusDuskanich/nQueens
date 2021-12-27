#include "Diagonal.h"

Diagonal::Diagonal(int squareDimension) : arrayLength(4 * squareDimension - 2), squareDimension(squareDimension){
    diagonals = new int[arrayLength]();
    validDiagonals = arrayLength;
}

Diagonal::~Diagonal() {
    delete[] diagonals;
    diagonals = nullptr;
    arrayLength = 0;
}

int Diagonal::negDiagonalIndexOf(Queen &q) const {
    return squareDimension - 1 + q.x - q.y;
}

int Diagonal::posDiagonalIndexOf(Queen &q) const {
    return 2 * squareDimension - 1 + q.x + q.y;
}

void Diagonal::add(Queen &q) {
    addQueenAndUpdateValidDiagonals(negDiagonalIndexOf(q));
    addQueenAndUpdateValidDiagonals(posDiagonalIndexOf(q));
}

void Diagonal::remove(Queen &q) {
    removeQueenAndUpdateValidDiagonals(negDiagonalIndexOf(q));
    removeQueenAndUpdateValidDiagonals(posDiagonalIndexOf(q));
}


bool Diagonal::isValidConfiguration() const {
    return arrayLength == validDiagonals;
}

void Diagonal::throwErrorIfIndexOutOfRange(int index) {
    if(indexOutOfRange(index)) {
        std::cout << index;
        throw std::out_of_range("Index out of range");
    }
}

int &Diagonal::at(int index) {
    throwErrorIfIndexOutOfRange(index);
    return diagonals[index];
}

bool Diagonal::indexOutOfRange(int index) const {
    return index < 0 || index >= arrayLength;
}

void Diagonal::reset() {
    for(int i = 0; i < arrayLength; i++){
        at(i) = 0;
    }
    validDiagonals = arrayLength;
}

int Diagonal::conflicts(Queen &q) {
    int queenCount = at(negDiagonalIndexOf(q)) + at(posDiagonalIndexOf(q)) - 2;
    if(queenCount < 0) throw std::runtime_error("diagonal update error");
    else return queenCount;
}

void Diagonal::print() {
    for (int i = 0; i < arrayLength; ++i) {
        std::cout << at(i) << " ";
    }
    std::cout << "validCnt: " << validDiagonals;
    std::cout << std::endl;
}

void Diagonal::removeQueenAndUpdateValidDiagonals(int index) {
    if(--at(index) == 1)
        validDiagonals++;
}

void Diagonal::addQueenAndUpdateValidDiagonals(int index) {
    if(++at(index) == 2)
        validDiagonals--;
}
