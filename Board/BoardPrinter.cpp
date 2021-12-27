#include "BoardPrinter.h"

BoardPrinter::BoardPrinter(FrameBuffer &frameBuffer) : frameBuffer(frameBuffer) {}

void BoardPrinter::setCursor(int x, int y) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD Position;
    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);
}

void BoardPrinter::print() {
    while (!frameBuffer.isEmpty()){
        QueenContainer frame = frameBuffer.readFromBuffer();
        setCursor();
        printBoardTiles(frame);
        printQueensOnBoard(frame);
        setCursor(0, frame.size());
        sleep();
    }
}

void BoardPrinter::printQueensOnBoard(const QueenContainer &frame) {
    for(int i = 0; i < frame.size(); i++){
        auto queen = frame.at(i);
        setCursor(queen.x * 2, queen.y);
        std::cout << "Q";
    }
}

void BoardPrinter::printBoardTiles(const QueenContainer &frame) {
    for(int i = 0; i < frame.size(); i++){
        for (int j = 0; j < frame.size(); ++j) {
            std::cout << "# ";
        }
        std::cout << std::endl;
    }
}

void BoardPrinter::sleep() {
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(50ms);
}
