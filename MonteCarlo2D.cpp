#include "classes.hpp"

std::vector<std::tuple<int, int>> MonteCarlo2D::prepareCoordinatesToProcess()
{
    std::vector<std::tuple<int, int>> coordinatesToProcess;
    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            coordinatesToProcess.push_back(std::make_tuple(i, j));
        }
    }
    return coordinatesToProcess;
}