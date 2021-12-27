#include "RandomUniqueCoordinateService.h"


RandomUniqueCoordinateService::RandomUniqueCoordinateService(int poolSize) : poolSize(poolSize) {}

void RandomUniqueCoordinateService::fillCoordinatePool() {
    throwErrorIfPoolFilled();
    fillPoolWithAscendingCoordinates();
    shuffle();
}

void RandomUniqueCoordinateService::fillPoolWithAscendingCoordinates() {
    for(int i = 0; i < poolSize; i++){
        XCoordinates.push_back(i);
        YCoordinates.push_back(i);
    }
}

void RandomUniqueCoordinateService::throwErrorIfPoolFilled() {
    if(!poolIsEmpty())
        throw std::runtime_error("Coordinate poll is not empty");
}

void RandomUniqueCoordinateService::shuffle() {
    std::default_random_engine engine(getSeed());
    std::shuffle(XCoordinates.begin(), XCoordinates.end(), engine);
    std::shuffle(YCoordinates.begin(), YCoordinates.end(), engine);
}

long long int RandomUniqueCoordinateService::getSeed() {
    static int seedOffset = 0;
    long long int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count() + seedOffset++;
    return seed;
}

std::pair<int, int> RandomUniqueCoordinateService::getNextCoordinate() {
    throwErrorIfPoolEmpty();
    auto nextCoordinate = front();
    pop_front();
    return nextCoordinate;
}

std::pair<int, int> RandomUniqueCoordinateService::front(){
    return {XCoordinates.front(), YCoordinates.front()};
}

void RandomUniqueCoordinateService::throwErrorIfPoolEmpty() {
    if(poolIsEmpty())
        throw std::runtime_error("Coordinate poll is empty");
}

void RandomUniqueCoordinateService::pop_front() {
    XCoordinates.pop_front();
    YCoordinates.pop_front();
}

bool RandomUniqueCoordinateService::poolIsEmpty() {
    return XCoordinates.empty() && YCoordinates.empty();
}
