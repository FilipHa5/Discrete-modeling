#include "classes.hpp"
#include <iostream>
#include <random>
#include <tuple>
#include <algorithm>
#include <vector>

CellularAutomata3D::CellularAutomata3D(std::string neighbourhood, bool isPeriodic, int cols, int rows, int depth, int nucleons)
    : Space(neighbourhood, isPeriodic, cols, rows, depth),
      nucleons(nucleons)
{
}

void CellularAutomata3D::printArrays()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < depth; ++k)
            {
                std::cout << grid_t3d[i][j][k] << ",";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void CellularAutomata3D::nucleate()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::vector<std::tuple<int, int, int>> coordinatesDone;

    std::uniform_int_distribution<int> uni_row(1, rows - 2);
    std::uniform_int_distribution<int> uni_col(1, cols - 2);
    std::uniform_int_distribution<int> uni_depth(1, cols - 2);


    int nucleonsCounter = 1;
    while (nucleonsCounter != nucleons)
    {
        int randomRow = uni_row(rng);
        int randomCol = uni_col(rng);
        int randomDepth = uni_depth(rng);


        std::tuple<int, int, int> coordinatesTriplet = std::make_tuple(randomRow, randomCol, randomDepth);

        if (std::find(coordinatesDone.begin(), coordinatesDone.end(), coordinatesTriplet) == coordinatesDone.end())
        {
            grid_t3d[randomRow][randomCol][randomDepth] = nucleonsCounter;
            grid_t13d[randomRow][randomCol] [randomDepth]= nucleonsCounter;

            coordinatesDone.push_back(coordinatesTriplet);
            nucleonsCounter++;
        }
    }
    std::cout << "Nucleated" << std::endl;
}

bool CellularAutomata3D::isDone() const
{
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            for (int k = 1; k < depth - 1; ++k)
                if (grid_t3d[i][j][k] == 0)
                    return false;
        }
    }
    return true;
}

void CellularAutomata3D::swapArrays()
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            for (int k = 0; k < depth; ++k)
            {
                grid_t3d[i][j][k] = grid_t13d[i][j][k];
                grid_t13d[i][j][k] = 0;
            }
        }
    }
}

void CellularAutomata3D::runCa()
{
    if (neighbourhood == "Moore")
    {
        std::cout << "Running Moore" << std::endl;
        while (!isDone())
        {
            applyBoundaryCondition();
            for (int i = 1; i < rows - 1; ++i)
            {
                for (int j = 1; j < cols - 1; ++j)
                {
                    for (int k = 1; k < depth - 1; ++k)
                    {
                        std::map<int, int> neighours = checkoutMooreNeighbourhood(grid_t3d, i, j, k);
                        int mode = getMode(neighours);
                        if (mode != 0)
                            grid_t13d[i][j][k] = mode;
                    }
                }
            }
            swapArrays();
        }
    }
    if (neighbourhood == "VonNeumann")
    {
        std::cout << "Running Von Neumann" << std::endl;
        while (!isDone())
        {
            for (int i = 1; i < rows - 1; ++i)
            {
                for (int j = 1; j < cols - 1; ++j)
                {
                    for (int k = 1; k < depth - 1; ++k)
                    {
                        applyBoundaryCondition();
                        std::map<int, int> neighours = checkoutVonNeumannNeighbourhood(grid_t3d, i, j, k);
                        int mode = getMode(neighours);
                        if (mode != 0)
                            grid_t13d[i][j][k] = mode;
                    }
                }
            }
            swapArrays();
        }
    }
}