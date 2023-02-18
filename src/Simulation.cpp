#include "classes.hpp"

#include <iostream>
#include <fstream>

Simulation::Simulation(std::string neighbourhood, bool isPeriodic,
                       int cols, int rows, int nucleons, int mcIter)
    : Obj2d(neighbourhood, isPeriodic, cols, rows, nucleons, mcIter),
      Obj3d(), is3d(false)
{
}

Simulation::Simulation(std::string neighbourhood, bool isPeriodic, int cols,
                       int rows, int depth, int nucleons, int mcIter)
    : Obj3d(neighbourhood, isPeriodic, cols, rows, depth, nucleons, mcIter),
      Obj2d(), is3d(true)
{
}

void Simulation::saveGrid(MonteCarlo3D &obj)
{
    int ***grid = Obj3d.getGridPtr();
    std::ofstream myfile("3D " + Obj3d.getNeighbourhood() + " " + std::to_string(Obj3d.getCols()) +
                         " " + std::to_string(Obj3d.getRows()) + " " + std::to_string(Obj3d.getDepth()) + 
                         " " + Obj3d.getBoundaryCondition() + ".txt");

    myfile << "3D CA Report, Nucleons" << Obj3d.getNucleons() << "\n";
    myfile << "Boundary condition: " << Obj3d.getBoundaryCondition() << "\n";
    myfile << "Neighbourhood: " << Obj3d.getNeighbourhood() << "\n";
    myfile << Obj3d.getCols() - 2 << "\n";
    myfile << Obj3d.getRows() - 2 << "\n";
    myfile << Obj3d.getDepth() - 2 << "\n";

    if (myfile.is_open())
    {
        myfile << "Row_nr, Col_nr, Depth_ index_nr, Value\n";
        for (int i = 1; i < Obj3d.getRows() - 1; ++i)
        {
            for (int j = 1; j < Obj3d.getCols() - 1; ++j)
            {
                for (int k = 1; k < Obj3d.getDepth() - 1; ++k)
                {
                    myfile << i - 1 << ',' << j - 1 << ',' << k - 1 << ',' << grid[i][j][k] << "\n";
                }
            }
        }
        std::cout << "Saved to file" << std::endl;
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

void Simulation::saveGrid(MonteCarlo2D &obj)
{
    int **grid = Obj2d.getGridPtr();

    std::ofstream myfile("2D " + Obj2d.getNeighbourhood() + " " + std::to_string(Obj2d.getCols() - 2) +
                         " " + std::to_string(Obj2d.getRows() - 2) + " " + Obj2d.getBoundaryCondition() + ".txt");

    if (myfile.is_open())
    {
        myfile << "Simulation 2D, Nucleons: " << Obj2d.getNucleons() << "\n";
        myfile << Obj2d.getCols() - 2 << "\n";
        myfile << Obj2d.getRows() - 2 << "\n";
        myfile << "0"
               << "\n";
        myfile << "Boundary condition: " << Obj2d.getBoundaryCondition() << "\n";
        myfile << "Neighbourhood: " << Obj2d.getNeighbourhood() << "\n";

        for (int i = 1; i < Obj2d.getRows() - 1; ++i)
        {
            for (int j = 1; j < Obj2d.getCols() - 1; j++)
            {
                myfile << grid[i][j] << ",";
            }
            myfile << "\n";
        }
        std::cout << "Saved to file" << std::endl;
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}

void Simulation::run()
{
    if (this->is3d == true)
    {
        // Cellular automata
        Obj3d.nucleate();
        Obj3d.runCa();
        Obj3d.printArrays();

        // Save to file
        this->saveGrid(Obj3d);

        // Monte Carlo
        Obj3d.runMcOpt();
        Obj3d.printArrays();
    }
    else
    {
        // Cellular automata
        Obj2d.nucleate();
        Obj2d.runCa();
        Obj2d.printArrays();

        // Save to file
        this->saveGrid(Obj2d);

        // Monte Carlo
        Obj2d.runMcOpt();
        Obj2d.printArrays();

        // Save to file
    }
}
