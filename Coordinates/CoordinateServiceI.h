#ifndef NQUEENS_COORDINATESERVICEI_H
#define NQUEENS_COORDINATESERVICEI_H
#include <utility>
class CoordinateServiceI{
public:
    virtual std::pair<int, int> getNextCoordinate() = 0;
    virtual void fillCoordinatePool() = 0;
    virtual bool poolIsEmpty() = 0;
};


#endif //NQUEENS_COORDINATESERVICEI_H
