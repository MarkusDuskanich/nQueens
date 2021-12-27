#ifndef NQUEENS_FRAMEBUFFER_H
#define NQUEENS_FRAMEBUFFER_H

#include "../Queen/QueenContainer.h"
#include <deque>

class FrameBuffer{
private:
    std::deque<QueenContainer> buffer;
    QueenContainer &currentFrame;

public:

    explicit FrameBuffer(QueenContainer &queens);
    void writeToBuffer();
    QueenContainer readFromBuffer();
    bool isEmpty();
};


#endif //NQUEENS_FRAMEBUFFER_H
