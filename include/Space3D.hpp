#pragma once

#include <map>
#include <string>

/******************************************************************************
                                Class Space3D
/******************************************************************************/

class Space3D
{
protected:
    int ***grid_t;
    int ***grid_t1;
    int cols;
    int rows;
    int depth;
    std::string neighbourhood;
    bool isPeriodic;

public:
    Space3D();
    Space3D(std::string, bool, int x, int y, int z);

    void applyBoundaryCondition();
    bool isEmpty() const;
    int getMode(std::map<int, int>) const;
    int getCols() const;
    int getRows() const;
    int getDepth() const;
    std::string getNeighbourhood();
    std::string getBoundaryCondition();
    std::map<int, int> checkoutMooreNeighbourhood(int ***, int, int, int) const;
    std::map<int, int> checkoutVonNeumannNeighbourhood(int ***, int, int, int) const;

    ~Space3D();
};