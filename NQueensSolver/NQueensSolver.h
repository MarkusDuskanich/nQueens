#ifndef NQUEENS_NQUEENSSOLVER_H
#define NQUEENS_NQUEENSSOLVER_H

#include "../Queen/QueenContainer.h"
#include "../Board/Board.h"
#include "../FrameBuffer/FrameBuffer.h"

class NQueensSolver {
private:
    Board &board;
    FrameBuffer &frameBuffer;
    int iterations = 0;

    void tryReachGlobalMinimum();
    bool attemptsLeftAndNotSolved(int &attempts);
    void tryReachLocalMinimum(int column);
    void tryReduceConflicts(int column1, int column2);
    static bool areConflictsIncreased(int conflictsBeforeSwap, int conflictsAfterSwap) ;
    int conflicts(int column1, int column2);
    void swap(int column1, int column2);

public:

    NQueensSolver(Board &board, FrameBuffer &frameBuffer);
    void solve(int attempts = 100);
    int getIterations() const;
};


#endif //NQUEENS_NQUEENSSOLVER_H
