#pragma once

#include <map>
#include <string>
#include <vector>
#include <tuple>

/******************************************************************************
                                Class Space
/******************************************************************************/

class Space
{
protected:
    int **grid_t;
    int **grid_t1;
    int ***grid_t3d;
    int ***grid_t13d;
    int cols;
    int rows;
    int depth;
    std::string neighbourhood;
    bool isPeriodic;

public:
    Space(std::string, bool, int x, int y);
    Space(std::string, bool, int x, int y, int z);

    void applyBoundaryCondition();
    bool isEmpty() const;
    int getMode(std::map<int, int>) const;

    std::map<int, int> checkoutMooreNeighbourhood(int **, int, int) const;
    std::map<int, int> checkoutMooreNeighbourhood(int ***, int, int, int) const;
    std::map<int, int> checkoutVonNeumannNeighbourhood(int **, int, int) const;
    std::map<int, int> checkoutVonNeumannNeighbourhood(int ***, int, int, int) const;

    ~Space();
};

class CellularAutomata2D : public Space
{
private:
    int nucleons;

public:
    CellularAutomata2D(std::string, bool, int, int, int);
    void nucleate();
    bool isDone() const;
    void swapArrays();
    void runCa();
    void printArrays();
};

class CellularAutomata3D : public Space
{
private:
    int nucleons;

public:
    void nucleate();
    bool isDone() const;
    void swapArrays();
    void runCa();
    void printArrays();
};

class MonteCarlo : public Space
{
protected:
    int steps;
    int calculateEnergy(int, std::map<int, int>);
    
public:
    void runMcClassic();
    void runMcOpt();
};

class MonteCarlo2D : public MonteCarlo
{
    std::vector<std::tuple<int, int>> prepareCoordinatesToProcess();
};

class MonteCarlo3D : public MonteCarlo
{
    std::vector<std::tuple<int, int, int>> prepareCoordinatesToProcess();
};