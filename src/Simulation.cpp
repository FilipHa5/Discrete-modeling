#include "classes.hpp"

Simulation::Simulation(std::string neighbourhood, bool isPeriodic, int cols, int rows, int nucleons, int mcIter)
    : Ca2d(neighbourhood, isPeriodic, cols, rows, nucleons), Mc2d(neighbourhood, isPeriodic, cols, rows, nucleons, mcIter)
{

}

void Simulation::run()
{
    Mc2d.nucleate();
    Mc2d.runCa();
    Mc2d.printArrays();
    Mc2d.runMcOpt();
    Mc2d.printArrays();
}
