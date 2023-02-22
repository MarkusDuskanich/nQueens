#include <iostream>
#include "Board/Board.h"
#include "Coordinates/RandomUniqueCoordinateService.h"
#include "NQueensSolver/NQueensSolver.h"
#include "Board/BoardPrinter.h"
#include "ConsoleInput/GetIntFromConsole.h"

using namespace std;


int main2(){
    //int boardSize = GetIntFromConsole().scan();
    int boardSize = 100000;

    auto tp1 = chrono::steady_clock::now();

    RandomUniqueCoordinateService coordinateService(boardSize);
    QueenContainer queens(boardSize);
    Board board(boardSize, queens, coordinateService);
    FrameBuffer frameBuffer(queens);
    BoardPrinter boardPrinter(frameBuffer);
    NQueensSolver nQueens(board, frameBuffer);

    nQueens.solve(100);

    auto tp2 = chrono::steady_clock::now();

    boardPrinter.print();

    if(board.isValidConfiguration()) cout << "Solved" << endl;
    else cout << "Could not solve in less than specified attempts" << endl;
    cout << "Iterations: " << nQueens.getIterations();
    cout << ", Board size: " << boardSize << "x" << boardSize << endl;
    cout <<  chrono::duration_cast<chrono::microseconds>(tp2 - tp1).count() << " microseconds, or about ";
    cout << chrono::duration_cast<chrono::milliseconds>(tp2 - tp1).count() << " milliseconds" << endl;

    system("Pause");
    return 0;
}
