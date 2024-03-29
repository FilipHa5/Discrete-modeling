#include <random>
#include <chrono>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "../include/MonteCarlo3D.hpp"

MonteCarlo3D::MonteCarlo3D()
{
}

MonteCarlo3D::MonteCarlo3D(std::string neighbourhood, bool isPeriodic, int cols, int rows, int depth, int nucleons, int steps)
    : CellularAutomata3D(neighbourhood, isPeriodic, cols, rows, depth, nucleons), steps(steps)
{
}

int MonteCarlo3D::calculateEnergy(int id, std::map<int, int> &neighbourhood)
{
    int energy = 0;
    for (auto const &p : neighbourhood)
    {
        if (p.first != id)
            energy++;
    }

    return energy;
}

std::vector<std::tuple<int, int, int>> MonteCarlo3D::prepareCoordinatesToProcess() const
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

void MonteCarlo3D::makeStepOnGrid(std::vector<std::tuple<int, int, int>> &coordinatesToProcess)
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
        int random_depth = std::get<2>(coordinatesToProcess[element]);

        if (this->neighbourhood == "Moore") // this if can be moved out of the loop to increase performance
        {
            std::map<int, int> neighbourhood = checkoutMooreNeighbourhood(grid_t, random_row, random_col, random_depth);
            int real_id = grid_t[random_row][random_col][random_depth];

            std::uniform_int_distribution<int> u_rand_hor(-1, 1);
            std::uniform_int_distribution<int> u_rand_vert(-1, 1);
            std::uniform_int_distribution<int> u_rand_depth(-1, 1);

            int hor_mask = u_rand_hor(rng);
            int vert_mask = u_rand_vert(rng);
            int depth_mask = u_rand_vert(rng);

            int temp_id = grid_t[random_row + hor_mask][random_col + vert_mask][random_depth + depth_mask];

            if (calculateEnergy(temp_id, neighbourhood) < calculateEnergy(real_id, neighbourhood) && calculateEnergy(temp_id, neighbourhood) != 0)
            {
                grid_t[random_row][random_col][random_depth] = temp_id;
            }
        }
        if (this->neighbourhood == "VonNeumann") // this if can be moved out of the loop to increase performance
        {
            std::map<int, int> neighbourhood = checkoutVonNeumannNeighbourhood(grid_t, random_row, random_col, random_depth);
            int real_id = grid_t[random_row][random_col][random_depth];

            std::uniform_int_distribution<int> u_rand_hor(-1, 1);
            std::uniform_int_distribution<int> u_rand_vert(-1, 1);
            std::uniform_int_distribution<int> u_rand_depth(-1, 1);

            int hor_mask = u_rand_hor(rng);
            int vert_mask = u_rand_vert(rng);
            int depth_mask = u_rand_vert(rng);

            int temp_id = grid_t[random_row + hor_mask][random_col + vert_mask][random_depth + depth_mask];

            if (calculateEnergy(temp_id, neighbourhood) < calculateEnergy(real_id, neighbourhood) && calculateEnergy(temp_id, neighbourhood) != 0)
            {
                grid_t[random_row][random_col][random_depth] = temp_id;
            }
        }
    }
}

void MonteCarlo3D::runMonteCarlo()
{
    std::cout << "Monte Carlo 3D start" << std::endl;

    for (int i = 0; i < this->steps; i++)
    {
        std::cout << "Step " << i << std::endl;
        std::vector<std::tuple<int, int, int>> coordinatesToProcess = prepareCoordinatesToProcess();
        makeStepOnGrid(coordinatesToProcess);
    }

    std::cout << "Monte Carlo 3D stop" << std::endl;
}
void MonteCarlo3D::saveToFile()
{
        std::ofstream myfile("3D report.txt");
        myfile << "Simulation 3D\n";
        myfile << cols - 2 << "\n";
        myfile << rows - 2 << "\n";
        myfile << depth - 2 << "\n";
        myfile << "MC Iter: " << steps << "\n";
        myfile << "Periodic BC: " << isPeriodic << "\n";
        myfile << "Neighbourhood: " << neighbourhood << "\n";


    if (myfile.is_open())
    {
        myfile << "Row_nr, Col_nr, Depth_ index_nr, Value\n";
        for (int i = 1; i < rows - 1; i++)
        {
            for (int j = 1; j < cols - 1; j++)
            {
                for (int k = 1; k < depth - 1; k++)
                {
                    myfile << i - 1 << ',' << j - 1 << ',' << k - 1 << ',' << grid_t[i][j][k] << "\n";
                }
            }
        }

        std::cout << "Saved to file" << std::endl;
        myfile.close();
    }
    else
        std::cout << "Unable to open file";
}
