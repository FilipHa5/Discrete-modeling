#include <iostream>
#include "../include/Space3D.hpp"

Space3D::Space3D()
{
}

void Space3D::allocateGrid()
{
    std::cout << "Space Allocator 3D" << std::endl;

    grid_t = new int **[this->rows];
    grid_t1 = new int **[this->rows];

    for (int i = 0; i < this->rows; i++)
    {
        grid_t[i] = new int *[this->cols];
        grid_t1[i] = new int *[this->cols];

        for (int j = 0; j < this->rows; j++)
        {
            grid_t[i][j] = new int[depth];
            grid_t1[i][j] = new int[depth];
        }
    }
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            for (int k = 0; k < this->depth; k++)
            {
                grid_t[i][j][k] = 0;
                grid_t1[i][j][k] = 0;
            }
        }
    }
}

Space3D::Space3D(std::string nieghbourhood, bool isPeriodic, int cols, int rows, int depth)
    : cols(cols + 2), rows(rows + 2), depth(depth + 2), isPeriodic(isPeriodic), neighbourhood(nieghbourhood)
{
    std::cout << "Space Constructor 3D" << std::endl;
}

Space3D::~Space3D()
{
    if (grid_t == nullptr && grid_t1 == nullptr)
    {
        std::cout << "Destructor 3D called" << std::endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
                delete[] grid_t[i][j];
                delete[] grid_t1[i][j];
            }
            delete[] grid_t[i];
            delete[] grid_t1[i];
        }

        delete[] grid_t;
        delete[] grid_t1;
    }
}

void Space3D::applyBoundaryCondition()
{
    for (int j = 1; j < cols - 1; j++)
    {
        for (int k = 1; k < depth - 1; k++)
        {
            grid_t[0][j][k] = grid_t[rows - 2][j][k]; // upper row
            grid_t[rows - 1][j][k] = grid_t[1][j][k]; // lower row
        }
    }
    for (int i = 1; i < rows - 1; i++)
    {
        for (int k = 1; k < depth - 1; k++)
        {
            grid_t[i][0][k] = grid_t[i][cols - 2][k]; // left side
            grid_t[i][cols - 1][k] = grid_t[i][1][k]; // right side
        }
    }

    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            grid_t[i][j][0] = grid_t[i][j][depth - 2]; // front side
            grid_t[i][j][depth - 1] = grid_t[i][j][1]; // back side
        }
    }

    grid_t[0][0][0] = grid_t[rows - 2][cols - 2][depth - 2]; // left upper frontal corner
    grid_t[0][cols - 1][0] = grid_t[rows - 2][1][depth - 2]; // right upper frontal corner

    grid_t[rows - 1][0][0] = grid_t[1][cols - 2][depth - 2]; // left lower frontal corner
    grid_t[rows - 1][cols - 1][0] = grid_t[1][1][depth - 2]; // right lower frontal corner

    grid_t[0][0][depth - 1] = grid_t[rows - 2][cols - 2][1]; // left upper back corner
    grid_t[0][cols - 1][depth - 1] = grid_t[rows - 2][1][1]; // right upper back corner

    grid_t[rows - 1][0][depth - 1] = grid_t[1][cols - 2][1]; // left lower back corner
    grid_t[rows - 1][cols - 1][depth - 1] = grid_t[1][1][1]; // right lower back corner
}

std::map<int, int> Space3D::checkoutMooreNeighbourhood(int ***grid_t, int i, int j, int k) const
{
    std::map<int, int> neighbours;

    neighbours[grid_t[i - 1][j - 1][k]]++;
    neighbours[grid_t[i - 1][j][k]]++;
    neighbours[grid_t[i - 1][j + 1][k]]++;
    neighbours[grid_t[i][j - 1][k]]++;
    neighbours[grid_t[i][j + 1][k]]++;
    neighbours[grid_t[i + 1][j - 1][k]]++;
    neighbours[grid_t[i + 1][j][k]]++;
    neighbours[grid_t[i + 1][j + 1][k]]++;

    neighbours[grid_t[i - 1][j - 1][k - 1]]++;
    neighbours[grid_t[i - 1][j][k - 1]]++;
    neighbours[grid_t[i - 1][j + 1][k - 1]]++;
    neighbours[grid_t[i][j - 1][k - 1]]++;
    neighbours[grid_t[i][j + 1][k - 1]]++;
    neighbours[grid_t[i + 1][j - 1][k - 1]]++;
    neighbours[grid_t[i + 1][j][k - 1]]++;
    neighbours[grid_t[i + 1][j + 1][k - 1]]++;

    neighbours[grid_t[i - 1][j - 1][k + 1]]++;
    neighbours[grid_t[i - 1][j][k + 1]]++;
    neighbours[grid_t[i - 1][j + 1][k + 1]]++;
    neighbours[grid_t[i][j - 1][k + 1]]++;
    neighbours[grid_t[i][j + 1][k + 1]]++;
    neighbours[grid_t[i + 1][j - 1][k + 1]]++;
    neighbours[grid_t[i + 1][j][k + 1]]++;
    neighbours[grid_t[i + 1][j + 1][k + 1]]++;

    neighbours[grid_t[i][j][k + 1]]++;
    neighbours[grid_t[i][j][k - 1]]++;

    return neighbours;
}

std::map<int, int> Space3D::checkoutVonNeumannNeighbourhood(int ***grid_t, int i, int j, int k) const
{
    static std::map<int, int> neighbours;
    neighbours[grid_t[i - 1][j][k]]++;
    neighbours[grid_t[i + 1][j][k]]++;
    neighbours[grid_t[i][j - 1][k]]++;
    neighbours[grid_t[i][j + 1][k]]++;

    neighbours[grid_t[i - 1][j][k + 1]]++;
    neighbours[grid_t[i + 1][j][k + 1]]++;
    neighbours[grid_t[i][j - 1][k + 1]]++;
    neighbours[grid_t[i][j + 1][k + 1]]++;

    neighbours[grid_t[i - 1][j][k - 1]]++;
    neighbours[grid_t[i + 1][j][k - 1]]++;
    neighbours[grid_t[i][j - 1][k - 1]]++;
    neighbours[grid_t[i][j + 1][k - 1]]++;

    neighbours[grid_t[i][j][k - 1]]++;
    neighbours[grid_t[i][j][k + 1]]++;

    return neighbours;
}