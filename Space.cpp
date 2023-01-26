#include "Space.h"
#include <iostream>

Space::Space(std::string nieghbourhood, bool isPeriodic, int cols, int rows)
    : cols(cols + 2), rows(rows + 2), isPeriodic(isPeriodic), neighbourhood(nieghbourhood)
{

    std::cout << "Space Constructor 2D" << std::endl;

    grid_t3d = nullptr;
    grid_t13d = nullptr;

    grid_t = new int *[rows];
    grid_t1 = new int *[rows];

    for (int i = 0; i < rows; i++)
    {
        grid_t[i] = new int[cols];
        grid_t1[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
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

    grid_t3d = new int **[rows];
    grid_t13d = new int **[rows];

    for (int i = 0; i < rows; i++)
    {
        grid_t3d[i] = new int *[cols];
        grid_t13d[i] = new int *[cols];

        for (int j = 0; j < cols; j++)
        {
            grid_t3d[i][j] = new int[depth];
            grid_t13d[i][j] = new int[depth];
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            for (int k = 0; k < depth; k++)
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
            for (int j = 0; j < cols; j++)
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

int Space::getMode(std::map<int, int> counter) const
{
    int tempMode = 0;
    int tempModeCounter = 0;
    for (auto const &p : counter)
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