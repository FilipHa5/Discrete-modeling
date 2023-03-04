#pragma once

#include <map>

class Simulation
{
public:
    virtual void allocateGrid() = 0;
    virtual void nucleate() = 0;
    virtual void runCellularAutomata() = 0;
    virtual void runMonteCarlo() = 0;
    virtual void saveToFile() = 0;

    virtual ~Simulation();
};