#include "classes.hpp"
#include <iostream>
#include <random>
#include <tuple>
#include <algorithm>
#include <vector>

CellularAutomata2D::CellularAutomata2D(std::string neighbourhood, bool isPeriodic, int cols, int rows, int nucleons)
    : Space(neighbourhood, isPeriodic, cols, rows),
      nucleons(nucleons)
{
}

void CellularAutomata2D::printArrays()
{
    for (int i = 0; i < cols; ++i)
    {
        for (int j = 0; j < rows; ++j)
        {
            std::cout << grid_t[i][j] << ",";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl
              << std::endl
              << std::endl;
}

void CellularAutomata2D::nucleate()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::vector<std::tuple<int, int>> coordinatesDone;

    std::uniform_int_distribution<int> uni_row(1, rows - 2);
    std::uniform_int_distribution<int> uni_col(1, cols - 2);

    int nucleonsCounter = 1;
    while (nucleonsCounter != nucleons)
    {
        int randomRow = uni_row(rng);
        int randomCol = uni_col(rng);

        std::tuple<int, int> coordinatesPair = std::make_tuple(randomRow, randomCol);

        if (std::find(coordinatesDone.begin(), coordinatesDone.end(), coordinatesPair) == coordinatesDone.end())
        {
            if (grid_t3d == nullptr)
            {
                grid_t[randomRow][randomCol] = nucleonsCounter;
                grid_t1[randomRow][randomCol] = nucleonsCounter;
            }
            coordinatesDone.push_back(coordinatesPair);
            nucleonsCounter++;
        }
    }
    std::cout << "Nucleated" << std::endl;
}

bool CellularAutomata2D::isDone() const
{
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            if (grid_t[i][j] == 0)
                return false;
        }
    }
    return true;
}

void CellularAutomata2D::swapArrays()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid_t[i][j] = grid_t1[i][j];
        }
    }
}

void CellularAutomata2D::runCa() // Code redundancy is on purpose due to performance issues
{
    if (neighbourhood == "Moore")
    {
        std::cout << "Running Moore" << std::endl;
        while (!isDone())
        {
            applyBoundaryCondition();
            for (int i = 1; i < rows - 1; i++)
            {
                for (int j = 1; j < cols - 1; j++)
                {
                    std::map<int, int> neighours = checkoutMooreNeighbourhood(grid_t, i, j);
                    int mode = getMode(neighours);
                    if (mode != 0)
                        grid_t1[i][j] = mode;
                }
            }
            swapArrays();
            printArrays();
        }
    }
    if (neighbourhood == "VonNeumann")
    {
        while (!isDone())
        {
            for (int i = 1; i < rows - 1; i++)
            {
                for (int j = 1; j < cols - 1; j++)
                {
                    applyBoundaryCondition();
                    std::map<int, int> neighours = checkoutVonNeumannNeighbourhood(grid_t, i, j);
                    int mode = getMode(neighours);
                    if (mode != 0)
                        grid_t1[i][j] = mode;
                }
            }
            swapArrays();
        }
    }
}