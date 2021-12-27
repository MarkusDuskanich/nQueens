#ifndef NQUEENS_BOARD_H
#define NQUEENS_BOARD_H

#include <iostream>
#include <chrono>
#include <thread>
#include "../Queen/Queen.h"
#include "../Coordinates/CoordinateServiceI.h"
#include "../Queen/QueenContainer.h"
#include "../Diagonal/Diagonal.h"
#include "../Coordinates/CoordinateServiceI.h"

class Board{
private:
    QueenContainer &queens;
    Diagonal diagonals;
    CoordinateServiceI &coordinateService;

    void addToDiagonals(Queen &q1, Queen &q2);
    static void swapYCoordinate(Queen &q1, Queen &q2);
    void removeFromDiagonals(Queen &q1, Queen &q2);
    void initialize();

public:

    Board(int dimension, QueenContainer &queens, CoordinateServiceI &coordinateService);

    Queen& getQueen(int index);
    int size();
    bool localMinimum(int column);
    void reset();
    int conflictsOfQueenTuple(Queen &q1, Queen &q2);
    bool isValidConfiguration();
    void swapRows(Queen &q1, Queen &q2);
};




#endif //NQUEENS_BOARD_H
