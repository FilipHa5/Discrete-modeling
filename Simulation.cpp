#include "Simulation.h"
#include <iostream>

bool Simulation::isDone() const
{
    if (!depth)
    {
        for (int i = 1; i < rows - 1; ++i)
        {
            for (int j = 1; j < cols - 1; j++)
            {
                return grid_t[i][j] != 0;
            }
        }
        return true;
    }

    else
    {
        for (int i = 1; i < rows - 1; ++i)
        {
            for (int j = 1; j < cols - 1; ++j)
            {
                for (int k = 1; k < depth.value() - 1; ++k)
                    return grid_t3d[i][j][k] != 0;
            }
        }
        return true;
    }
}

void Simulation::swapArrays()
{
    if (!depth)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                for (int k = 0; k < depth.value(); k++)
                {
                    grid_t3d[i][j][k] = grid_t13d[i][j][k];
                    grid_t13d[i][j][k] = 0;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid_t[i][j] = grid_t1[i][j];
            }
        }
    }
}

int Simulation::getMode(std::map<int, int> neighbours) const
{
    int tempMode = 0;
    int tempModeCounter = 0;
    for (auto const &p : neighbours)
    {
        if (p.first != 0)
        {
            if (p.second > tempModeCounter)
            {
                tempMode = p.first;
                tempModeCounter = p.second;
            }
        }
    }
    return tempMode;
}

void Simulation::run2d() // Code redundancy is on purpose due to performance issues
{
    if (neighbourhood == "Moore")
    {
        std::cout << "Running Moore" << std::endl;
        while (!isDone())
        {
            for (int i = 1; i < rows - 1; i++)
            {
                for (int j = 1; j < cols - 1; j++)
                {
                    applyBoundaryCondition();
                    static std::map<int, int> neighours = checkoutMooreNeighbourhood(grid_t, i, j);
                    int mode = getMode(neighours);
                    if (mode != 0)
                        grid_t1[i][j] = mode;
                }
            }
            swapArrays();
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
                    static std::map<int, int> neighours = checkoutVonNeumannNeighbourhood(grid_t, i, j);
                    int mode = getMode(neighours);
                    if (mode != 0)
                        grid_t1[i][j] = mode;
                }
            }
            swapArrays();
        }
    }
}

void Simulation::run()
{
    if (!depth)
    {
        run2d();
    }
    else
    {
        run3d();
    }   
}