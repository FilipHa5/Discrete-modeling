#pragma once

#include <map>
#include <string>
#include "Simulation.hpp"

/******************************************************************************
                                Class Space3D
/******************************************************************************/

class Space3D : public Simulation
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

    void allocateGrid() override;
    void applyBoundaryCondition();
    bool isEmpty() const;
    int getCols() const;
    int getRows() const;
    int getDepth() const;
    std::string getNeighbourhood();
    std::string getBoundaryCondition();
    std::map<int, int> checkoutMooreNeighbourhood(int ***, int, int, int) const;
    std::map<int, int> checkoutVonNeumannNeighbourhood(int ***, int, int, int) const;

    ~Space3D();
};