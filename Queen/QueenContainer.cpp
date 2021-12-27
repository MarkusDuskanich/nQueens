#include "QueenContainer.h"

QueenContainer::QueenContainer(int length) : length(length), queens(new Queen[length]()) {}


QueenContainer::~QueenContainer() {
    delete[] queens;
    queens = nullptr;
    length = 0;
}

Queen& QueenContainer::at(int index) const {
    throwErrorIfOutOfRange(index);
    return queens[index];
}

bool QueenContainer::indexOutOfRange(int index) const {
    return index < 0 || index >= length;
}

void QueenContainer::throwErrorIfOutOfRange(int index) const {
    if(indexOutOfRange(index))
        throw std::out_of_range("Index out of range");
}

int QueenContainer::size() const {
    return length;
}

QueenContainer::QueenContainer(const QueenContainer &origin) : length(origin.length), queens(new Queen[origin.length]()){
    for (int i = 0; i < length; ++i) {
        at(i) = origin.at(i);
    }
}
