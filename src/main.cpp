#include <memory>
#include "../include/Simulation.hpp"
#include "../include/Space2D.hpp"
#include "../include/Space3D.hpp"
#include "../include/CellularAutomata2D.hpp"
#include "../include/CellularAutomata3D.hpp"
#include "../include/MonteCarlo2D.hpp"
#include "../include/MonteCarlo3D.hpp"

int main(int argc, char *argv[])
{
    int cols, rows, depth, nucleons, steps;
    std::string neighbourhood;
    bool isPeriodic;

    cols = 10;
    rows = 10;
    depth = 0;
    neighbourhood = "Moore";
    isPeriodic = true;
    nucleons = 9;
    steps = 100;

    std::unique_ptr<Simulation> s(new MonteCarlo2D(neighbourhood, isPeriodic, cols, rows, nucleons, steps));
    //Simulation* s = new MonteCarlo2D(neighbourhood, isPeriodic, cols, rows, nucleons, steps);

    s->allocateGrid();
    s->nucleate();
    s->runCellularAutomata();
    
    //delete s;

    return 0;
}