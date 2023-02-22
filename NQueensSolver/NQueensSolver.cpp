#include "NQueensSolver.h"

NQueensSolver::NQueensSolver(Board &board, FrameBuffer &frameBuffer) : board(board), frameBuffer(frameBuffer){}

void NQueensSolver::solve(int attempts) {
    while(attemptsLeftAndNotSolved(attempts)){
        tryReachGlobalMinimum();
        if(!board.isValidConfiguration())
            board.reset();
    }
}

bool NQueensSolver::attemptsLeftAndNotSolved(int &attempts) {
    return attempts-- && !board.isValidConfiguration();
}

void NQueensSolver::tryReachGlobalMinimum() {
    for (int column = 0; column < board.size() - 1; ++column) {
        tryReachLocalMinimum(column);
        if(board.isValidConfiguration())
            return;
    }
}

void NQueensSolver::tryReachLocalMinimum(int column) {
    for (int column2 = column + 1; column2 < board.size(); ++column2) {
        iterations++;
        tryReduceConflicts(column, column2);
        if(board.localMinimum(column)) return;
    }
}


void NQueensSolver::tryReduceConflicts(int column1, int column2) {
    int conflictsBeforeSwap = conflicts(column1, column2);
    swap(column1, column2);
    int conflictsAfterSwap = conflicts(column1, column2);
    if (areConflictsIncreased(conflictsBeforeSwap, conflictsAfterSwap)) swap(column1, column2);
    else if(board.size() <= 16) frameBuffer.writeToBuffer();
}

void NQueensSolver::swap(int column1, int column2) {
    board.swapRows(board.getQueen(column1), board.getQueen(column2));
}

int NQueensSolver::conflicts(int column1, int column2) {
    return board.conflictsOfQueenTuple(board.getQueen(column1), board.getQueen(column2));
}

bool NQueensSolver::areConflictsIncreased(int conflictsBeforeSwap, int conflictsAfterSwap) {
    return conflictsAfterSwap > conflictsBeforeSwap;
}

int NQueensSolver::getIterations() const {
    return iterations;
}