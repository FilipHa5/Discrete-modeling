#pragma once

#include <string>
#include <map>
#include "Simulation.hpp"

/******************************************************************************
                                Class Space2D
/******************************************************************************/

class Space2D : public Simulation
{
protected:
    int **grid_t;
    int **grid_t1;
    int cols;
    int rows;
    std::string neighbourhood;
    bool isPeriodic;

public:
    Space2D();
    Space2D(std::string, bool, int, int);

    void allocateGrid() override;
    void applyBoundaryCondition();
    bool isEmpty() const;
    int getCols() const;
    int getRows() const;
    std::string getNeighbourhood() const;
    std::string getBoundaryCondition() const;
    std::map<int, int> checkoutMooreNeighbourhood(int **, int, int) const;
    std::map<int, int> checkoutVonNeumannNeighbourhood(int **, int, int) const;

    ~Space2D();
};