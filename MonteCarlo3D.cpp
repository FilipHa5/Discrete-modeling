#include "classes.hpp"

std::vector<std::tuple<int, int, int>> MonteCarlo3D::prepareCoordinatesToProcess()
{
    std::vector<std::tuple<int, int, int>> coordinatesToProcess;
    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            for (int k = 1; k < depth - 1; k++)
            {
                coordinatesToProcess.push_back(std::make_tuple(i, j, k));
            }
        }
    }
    return coordinatesToProcess;
}