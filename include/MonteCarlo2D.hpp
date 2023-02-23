#pragma once

#include <map>
#include <string>
#include <vector>
#include <tuple>
#include "CellularAutomata2D.hpp"

/******************************************************************************
                                Class MonteCarlo2D
/******************************************************************************/

class MonteCarlo2D : public CellularAutomata2D
{
protected:
    int steps;
    int calculateEnergy(int, std::map<int, int>&);
public:
    MonteCarlo2D();
    MonteCarlo2D(std::string, bool, int, int, int, int);
    std::vector<std::tuple<int, int>> prepareCoordinatesToProcess() const;
    void makeStepOnGrid(std::vector<std::tuple<int, int>> &coordinates);
    void runMcOpt();
};