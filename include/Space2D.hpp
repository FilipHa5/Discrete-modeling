#pragma once

#include <string>
#include <map>

/******************************************************************************
                                Class Space2D
/******************************************************************************/

class Space2D
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

    void applyBoundaryCondition();
    bool isEmpty() const;
    int getMode(std::map<int, int>) const;
    int getCols() const;
    int getRows() const;
    std::string getNeighbourhood() const;
    std::string getBoundaryCondition() const;
    std::map<int, int> checkoutMooreNeighbourhood(int **, int, int) const;
    std::map<int, int> checkoutVonNeumannNeighbourhood(int **, int, int) const;

    ~Space2D();
};