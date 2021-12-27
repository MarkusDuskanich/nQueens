#ifndef NQUEENS_RANDOMUNIQUECOORDINATESERVICE_H
#define NQUEENS_RANDOMUNIQUECOORDINATESERVICE_H

#include <random>
#include <algorithm>
#include <deque>
#include <chrono>
#include "CoordinateServiceI.h"
#include <stdexcept>

class  RandomUniqueCoordinateService : public CoordinateServiceI{
private:
    std::deque<int> XCoordinates;
    std::deque<int> YCoordinates;
    int poolSize;

    void shuffle();
    void pop_front();
    void throwErrorIfPoolFilled();
    void throwErrorIfPoolEmpty();
    void fillPoolWithAscendingCoordinates();
    std::pair<int, int> front();
    static long long int getSeed();

public:
    explicit RandomUniqueCoordinateService(int poolSize);
    void fillCoordinatePool() override;
    std::pair<int, int> getNextCoordinate() override;
    bool poolIsEmpty() override;
};


#endif //NQUEENS_RANDOMUNIQUECOORDINATESERVICE_H
