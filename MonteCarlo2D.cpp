#include "classes.hpp"
#include <random>
#include <chrono>
#include <tuple>

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

void MonteCarlo2D::makeStepOnGrid(std::vector<std::tuple<int, int>> &coordinatesToProcess)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    std::shuffle(std::begin(coordinatesToProcess), std::end(coordinatesToProcess), e);
    for (unsigned int element = 0; element < coordinatesToProcess.size(); element++)
    {
        applyBoundaryCondition();

        int random_row = std::get<0>(coordinatesToProcess[element]);
        int random_col = std::get<1>(coordinatesToProcess[element]);

        if (this->neighbourhood == "Moore")
        {
            std::map<int, int> neighbourhood = checkoutMooreNeighbourhood(grid_t, random_row, random_col);
            int real_id = grid_t[random_row][random_col];

            std::uniform_int_distribution<int> u_rand_hor(-1, 1);
            std::uniform_int_distribution<int> u_rand_vert(-1, 1);

            int hor_mask = u_rand_hor(rng);
            int vert_mask = u_rand_vert(rng);

            int temp_id = grid_t[random_row + hor_mask][random_col + vert_mask];

            if (calculateEnergy(temp_id, neighbourhood) < calculateEnergy(real_id, neighbourhood) && calculateEnergy(temp_id, neighbourhood) != 0)
            {
                grid_t[random_row][random_col] = temp_id;
            }
        }
    }
}