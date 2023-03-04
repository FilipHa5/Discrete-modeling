#include "../include/Space2D.hpp"
#include <iostream>

Space2D::Space2D()
{
}

void Space2D::allocateGrid()
{
    std::cout << "Space Allocator 2D" << std::endl;

    grid_t = new int *[this->rows];
    grid_t1 = new int *[this->rows];

    for (int i = 0; i < this->rows; i++)
    {
        grid_t[i] = new int[this->rows];
        grid_t1[i] = new int[this->rows];
    }

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            grid_t[i][j] = 0;
            grid_t1[i][j] = 0;
        }
    }
}

Space2D::Space2D(std::string nieghbourhood, bool isPeriodic, int cols, int rows)
    : isPeriodic(isPeriodic), neighbourhood(nieghbourhood), rows(rows + 2), cols(cols + 2)
{
    std::cout << "Space Constructor 2D" << std::endl;
}

Space2D::~Space2D()
{
    std::cout << "Destructor 2D called" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        delete[] grid_t[i];
        delete[] grid_t1[i];
    }
    delete[] grid_t;
    delete[] grid_t1;
}
void Space2D::applyBoundaryCondition()
{
    for (int j = 1; j < cols - 1; j++)
    {
        grid_t[0][j] = grid_t[rows - 2][j]; // upper row
        grid_t[rows - 1][j] = grid_t[1][j]; // lower row
    }
    for (int i = 1; i < rows - 1; i++)
    {
        grid_t[i][0] = grid_t[i][cols - 2]; // left side
        grid_t[i][cols - 1] = grid_t[i][1]; // right side
    }
    grid_t[0][0] = grid_t[rows - 2][cols - 2]; // left upper corner
    grid_t[0][cols - 1] = grid_t[rows - 2][1]; // right upper corner

    grid_t[rows - 1][0] = grid_t[1][cols - 2]; // left lower corner
    grid_t[rows - 1][cols - 1] = grid_t[1][1]; // right lower corner
}

std::map<int, int> Space2D::checkoutMooreNeighbourhood(int **grid_t, int i, int j) const
{
    std::map<int, int> neighbours;

    neighbours[grid_t[i - 1][j - 1]]++;
    neighbours[grid_t[i - 1][j]]++;
    neighbours[grid_t[i - 1][j + 1]]++;
    neighbours[grid_t[i][j - 1]]++;
    neighbours[grid_t[i][j + 1]]++;
    neighbours[grid_t[i + 1][j - 1]]++;
    neighbours[grid_t[i + 1][j]]++;
    neighbours[grid_t[i + 1][j + 1]]++;

    return neighbours;
}

std::map<int, int> Space2D::checkoutVonNeumannNeighbourhood(int **grid_t, int i, int j) const
{
    static std::map<int, int> neighbours;

    neighbours[grid_t[i - 1][j]]++;
    neighbours[grid_t[i + 1][j]]++;
    neighbours[grid_t[i][j - 1]]++;
    neighbours[grid_t[i][j + 1]]++;

    return neighbours;
}
