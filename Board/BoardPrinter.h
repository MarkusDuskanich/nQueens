//
// Created by Markus on 14.07.2021.
//

#ifndef NQUEENS_BOARDPRINTER_H
#define NQUEENS_BOARDPRINTER_H

#include "../FrameBuffer/FrameBuffer.h"
#include <windows.h>
#include <iostream>
#include <thread>

class BoardPrinter {
private:
    FrameBuffer &frameBuffer;
    static void setCursor(int x = 0, int y = 0);
    static void printBoardTiles(const QueenContainer &frame) ;
    static void printQueensOnBoard(const QueenContainer &frame) ;
    static void sleep();

public:
    explicit BoardPrinter(FrameBuffer &frameBuffer);
    void print();
};


#endif //NQUEENS_BOARDPRINTER_H
