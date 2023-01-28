#include "MonteCarlo.h"
#include "File.h"
#include "Space.h"

class Simulation : public Space
{
    void makeNucleation();
    bool isDone() const;
    void run();
    void run2d();
    void run3d();
    void swapArrays();

    int getMode(std::map <int, int>) const;
};