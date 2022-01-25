#ifndef NQUEENS_ICOORDINATESERVICE_H
#define NQUEENS_ICOORDINATESERVICE_H
#include <utility>
class ICoordinateService{
public:
    virtual std::pair<int, int> getNextCoordinate() = 0;
    virtual void fillCoordinatePool() = 0;
    virtual bool poolIsEmpty() = 0;
};


#endif //NQUEENS_ICOORDINATESERVICE_H
