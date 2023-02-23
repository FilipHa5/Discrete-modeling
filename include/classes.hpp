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
    Space();
    Space(std::string, bool, int x, int y);
    Space(std::string, bool, int x, int y, int z);

    void applyBoundaryCondition();
    bool isEmpty() const;
    int getMode(std::map<int, int>) const;
    int getCols();
    int getRows();
    int getDepth();
    std::string getNeighbourhood();
    std::string getBoundaryCondition();


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
    CellularAutomata2D();
    CellularAutomata2D(std::string, bool, int, int, int);
    void nucleate();
    bool isDone() const;
    void swapArrays();
    void runCa();
    void printArrays();
    int getNucleons();
};

class CellularAutomata3D : public Space
{
private:
    int nucleons;

public:
    CellularAutomata3D();
    CellularAutomata3D(std::string, bool, int, int, int, int);
    void nucleate();
    bool isDone() const;
    void swapArrays();
    void runCa();
    void printArrays();
    int getNucleons();
};

class MonteCarlo2D : public CellularAutomata2D
{
protected:
    int steps;
    int calculateEnergy(int, std::map<int, int>&);
public:
    MonteCarlo2D();
    MonteCarlo2D(std::string, bool, int, int, int, int);
    std::vector<std::tuple<int, int>> prepareCoordinatesToProcess();
    void makeStepOnGrid(std::vector<std::tuple<int, int>> &coordinates);
    void runMcOpt();
    int ** getGridPtr();
};

class MonteCarlo3D : public CellularAutomata3D
{ 
protected:
    int steps;
    int calculateEnergy(int, std::map<int, int>&);

public:
    MonteCarlo3D();
    MonteCarlo3D(std::string, bool, int, int, int, int, int);
    std::vector<std::tuple<int, int, int>> prepareCoordinatesToProcess();
    void makeStepOnGrid(std::vector<std::tuple<int, int, int>> &coordinates);
    void runMcOpt();
    int *** getGridPtr();
};

class Simulation
{
private:
    bool is3d;

protected:
    MonteCarlo2D Obj2d;
    MonteCarlo3D Obj3d;

public:
    Simulation(std::string, bool, int, int, int, int);
    Simulation(std::string, bool, int, int, int, int, int);

    void run();
    void saveGrid(MonteCarlo3D&);
    void saveGrid(MonteCarlo2D&);
};
