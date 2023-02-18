#include "classes.hpp"
#include <iostream>

Space::Space()
{
}

Space::Space(std::string nieghbourhood, bool isPeriodic, int cols, int rows)
    : isPeriodic(isPeriodic), neighbourhood(nieghbourhood)
{
    this->cols = cols + 2;
    this->rows = rows + 2;
    this->depth = 0;

    std::cout << "Space Constructor 2D" << std::endl;
    std::cout << "Cols:"<<this->cols;
    std::cout << "Rows:"<<this->rows;

    grid_t3d = nullptr;
    grid_t13d = nullptr;

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

Space::Space(std::string nieghbourhood, bool isPeriodic, int cols, int rows, int depth)
    : cols(cols + 2), rows(rows + 2), depth(depth + 2), isPeriodic(isPeriodic), neighbourhood(nieghbourhood)
{

    std::cout << "Space Constructor 3D" << std::endl;

    grid_t = nullptr;
    grid_t1 = nullptr;

    grid_t3d = new int **[this->rows];
    grid_t13d = new int **[this->rows];

    for (int i = 0; i < this->rows; i++)
    {
        grid_t3d[i] = new int *[this->cols];
        grid_t13d[i] = new int *[this->cols];

        for (int j = 0; j < this->rows; j++)
        {
            grid_t3d[i][j] = new int[depth];
            grid_t13d[i][j] = new int[depth];
        }
    }
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            for (int k = 0; k < this->depth; k++)
            {
                grid_t3d[i][j][k] = 0;
                grid_t13d[i][j][k] = 0;
            }
        }
    }
}

Space::~Space()
{
    if (grid_t == nullptr && grid_t1 == nullptr)
    {
        std::cout << "Destructor 3D called" << std::endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < this->rows; j++)
            {
                delete[] grid_t3d[i][j];
                delete[] grid_t13d[i][j];
            }
            delete[] grid_t3d[i];
            delete[] grid_t13d[i];
        }

        delete[] grid_t3d;
        delete[] grid_t13d;
    }

    if (grid_t3d == nullptr && grid_t13d == nullptr)
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
}
void Space::applyBoundaryCondition()
{
    if (grid_t != nullptr && isPeriodic == true)
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

    if (grid_t3d != nullptr && isPeriodic == true)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            for (int k = 1; k < depth - 1; k++)
            {
                grid_t3d[0][j][k] = grid_t3d[rows - 2][j][k]; // upper row
                grid_t3d[rows - 1][j][k] = grid_t3d[1][j][k]; // lower row
            }
        }
        for (int i = 1; i < rows - 1; i++)
        {
            for (int k = 1; k < depth - 1; k++)
            {
                grid_t3d[i][0][k] = grid_t3d[i][cols - 2][k]; // left side
                grid_t3d[i][cols - 1][k] = grid_t3d[i][1][k]; // right side
            }
        }

        for (int i = 1; i < rows - 1; i++)
        {
            for (int j = 1; j < cols - 1; j++)
            {
                grid_t3d[i][j][0] = grid_t3d[i][j][depth - 2]; // front side
                grid_t3d[i][j][depth - 1] = grid_t3d[i][j][1]; // back side
            }
        }

        grid_t3d[0][0][0] = grid_t3d[rows - 2][cols - 2][depth - 2]; // left upper frontal corner
        grid_t3d[0][cols - 1][0] = grid_t3d[rows - 2][1][depth - 2]; // right upper frontal corner

        grid_t3d[rows - 1][0][0] = grid_t3d[1][cols - 2][depth - 2]; // left lower frontal corner
        grid_t3d[rows - 1][cols - 1][0] = grid_t3d[1][1][depth - 2]; // right lower frontal corner

        grid_t3d[0][0][depth - 1] = grid_t3d[rows - 2][cols - 2][1]; // left upper back corner
        grid_t3d[0][cols - 1][depth - 1] = grid_t3d[rows - 2][1][1]; // right upper back corner

        grid_t3d[rows - 1][0][depth - 1] = grid_t3d[1][cols - 2][1]; // left lower back corner
        grid_t3d[rows - 1][cols - 1][depth - 1] = grid_t3d[1][1][1]; // right lower back corner
    }
}

std::map<int, int> Space::checkoutMooreNeighbourhood(int **grid_t, int i, int j) const
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

std::map<int, int> Space::checkoutMooreNeighbourhood(int ***grid_t3d, int i, int j, int k) const
{
    static std::map<int, int> neighbours;

    neighbours[grid_t3d[i - 1][j - 1][k]]++;
    neighbours[grid_t3d[i - 1][j][k]]++;
    neighbours[grid_t3d[i - 1][j + 1][k]]++;
    neighbours[grid_t3d[i][j - 1][k]]++;
    neighbours[grid_t3d[i][j + 1][k]]++;
    neighbours[grid_t3d[i + 1][j - 1][k]]++;
    neighbours[grid_t3d[i + 1][j][k]]++;
    neighbours[grid_t3d[i + 1][j + 1][k]]++;

    neighbours[grid_t3d[i - 1][j - 1][k - 1]]++;
    neighbours[grid_t3d[i - 1][j][k - 1]]++;
    neighbours[grid_t3d[i - 1][j + 1][k - 1]]++;
    neighbours[grid_t3d[i][j - 1][k - 1]]++;
    neighbours[grid_t3d[i][j + 1][k - 1]]++;
    neighbours[grid_t3d[i + 1][j - 1][k - 1]]++;
    neighbours[grid_t3d[i + 1][j][k - 1]]++;
    neighbours[grid_t3d[i + 1][j + 1][k - 1]]++;

    neighbours[grid_t3d[i - 1][j - 1][k + 1]]++;
    neighbours[grid_t3d[i - 1][j][k + 1]]++;
    neighbours[grid_t3d[i - 1][j + 1][k + 1]]++;
    neighbours[grid_t3d[i][j - 1][k + 1]]++;
    neighbours[grid_t3d[i][j + 1][k + 1]]++;
    neighbours[grid_t3d[i + 1][j - 1][k + 1]]++;
    neighbours[grid_t3d[i + 1][j][k + 1]]++;
    neighbours[grid_t3d[i + 1][j + 1][k + 1]]++;

    neighbours[grid_t3d[i][j][k + 1]]++;
    neighbours[grid_t3d[i][j][k - 1]]++;

    return neighbours;
}

std::map<int, int> Space::checkoutVonNeumannNeighbourhood(int **grid_t, int i, int j) const
{
    static std::map<int, int> neighbours;

    neighbours[grid_t[i - 1][j]]++;
    neighbours[grid_t[i + 1][j]]++;
    neighbours[grid_t[i][j - 1]]++;
    neighbours[grid_t[i][j + 1]]++;

    return neighbours;
}

std::map<int, int> Space::checkoutVonNeumannNeighbourhood(int ***grid_t3d, int i, int j, int k) const
{
    static std::map<int, int> neighbours;
    neighbours[grid_t3d[i - 1][j][k]]++;
    neighbours[grid_t3d[i + 1][j][k]]++;
    neighbours[grid_t3d[i][j - 1][k]]++;
    neighbours[grid_t3d[i][j + 1][k]]++;

    neighbours[grid_t3d[i - 1][j][k + 1]]++;
    neighbours[grid_t3d[i + 1][j][k + 1]]++;
    neighbours[grid_t3d[i][j - 1][k + 1]]++;
    neighbours[grid_t3d[i][j + 1][k + 1]]++;

    neighbours[grid_t3d[i - 1][j][k - 1]]++;
    neighbours[grid_t3d[i + 1][j][k - 1]]++;
    neighbours[grid_t3d[i][j - 1][k - 1]]++;
    neighbours[grid_t3d[i][j + 1][k - 1]]++;

    neighbours[grid_t3d[i][j][k - 1]]++;
    neighbours[grid_t3d[i][j][k + 1]]++;

    return neighbours;
}

int Space::getMode(std::map<int, int> counter) const 
{
    int most_common_value=0;
    int most_common_counter=0;
    for (auto const& p : counter)
    {
        if (p.first !=0)
        {
            if (p.second > most_common_counter)
            {
                most_common_value = p.first;
                most_common_counter = p.second;
            }
        }
    }
    return most_common_value;
}

