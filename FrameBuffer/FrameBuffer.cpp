#include "FrameBuffer.h"

void FrameBuffer::writeToBuffer() {
    buffer.push_back(currentFrame);
}

QueenContainer FrameBuffer::readFromBuffer() {
    auto nextFrame = buffer.front();
    buffer.pop_front();
    return nextFrame;
}

bool FrameBuffer::isEmpty() {
    return buffer.empty();
}

FrameBuffer::FrameBuffer(QueenContainer &queens) : currentFrame(queens) {}