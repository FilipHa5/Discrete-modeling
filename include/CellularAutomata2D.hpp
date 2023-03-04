#pragma once

#include <string>
#include "Space2D.hpp"

/******************************************************************************
                            Class Cellular Automata 2D
/******************************************************************************/

class CellularAutomata2D : public Space2D
{
private:
    int nucleons;

public:
    CellularAutomata2D();
    CellularAutomata2D(std::string, bool, int, int, int);
    void nucleate() override;
    bool isDone() const;
    void swapArrays();
    void runCellularAutomata() override;
    void printArrays();
    int getNucleons();
};
