#pragma once

#include <map>
#include <string>
#include <vector>
#include <tuple>
#include "CellularAutomata3D.hpp"

/******************************************************************************
                                Class MonteCarlo3D
/******************************************************************************/

class MonteCarlo3D : public CellularAutomata3D
{
protected:
    int steps;
    int calculateEnergy(int, std::map<int, int> &);

public:
    MonteCarlo3D();
    MonteCarlo3D(std::string, bool, int, int, int, int, int);
    std::vector<std::tuple<int, int, int>> prepareCoordinatesToProcess() const;
    void makeStepOnGrid(std::vector<std::tuple<int, int, int>> &coordinates);
    void runMonteCarlo() override;
    void saveToFile() override;
};