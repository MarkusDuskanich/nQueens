#include "Board.h"

Board::Board(int dimension, QueenContainer &queens, ICoordinateService &coordinateService) : queens(queens),
                                                                                             diagonals(dimension), coordinateService(coordinateService) {
    if(dimension < 4)
        throw std::runtime_error("Dimension of bord must be >= 4");
    initialize();
}

bool Board::isValidConfiguration() {
    return diagonals.isValidConfiguration();
}

void Board::initialize() {
    coordinateService.fillCoordinatePool();
    for (int i = 0; i < queens.size(); ++i) {
        auto coordinate = coordinateService.getNextCoordinate();
        Queen newQueen(coordinate.first, coordinate.second);
        queens.at(i) = newQueen;
        diagonals.add(newQueen);
    }
}

void Board::addToDiagonals(Queen &q1, Queen &q2) {
    diagonals.add(q1);
    diagonals.add(q2);
}

void Board::removeFromDiagonals(Queen &q1, Queen &q2) {
    diagonals.remove(q1);
    diagonals.remove(q2);
}

bool Board::localMinimum(int column) {
    return diagonals.conflicts(queens.at(column)) == 0;
}

void Board::swapRows(Queen &q1, Queen &q2) {
    removeFromDiagonals(q1, q2);
    swapYCoordinate(q1, q2);
    addToDiagonals(q1, q2);
}

void Board::swapYCoordinate(Queen &q1, Queen &q2) {
    int temp = q1.y;
    q1.y = q2.y;
    q2.y = temp;
}

int Board::conflictsOfQueenTuple(Queen &q1, Queen &q2) {
    return diagonals.conflicts(q1) + diagonals.conflicts(q2);
}

void Board::reset() {
    diagonals.reset();
    initialize();
}

int Board::size() {
    return queens.size();
}

Queen &Board::getQueen(int index) {
    return queens.at(index);
}
