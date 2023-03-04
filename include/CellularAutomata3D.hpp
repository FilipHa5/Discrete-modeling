#pragma once

#include <string>
#include "Space3D.hpp"

/******************************************************************************
                            Class Cellular Automata 3D
/******************************************************************************/

class CellularAutomata3D : public Space3D
{
private:
    int nucleons;

public:
    CellularAutomata3D();
    CellularAutomata3D(std::string, bool, int, int, int, int);
    void nucleate() override;
    bool isDone() const;
    void swapArrays();
    void runCellularAutomata() override;
    void printArrays();
    int getNucleons();
};