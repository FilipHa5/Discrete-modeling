#include "classes.hpp"

int main(int argc,char* argv[])
{
    MonteCarlo2D s1("Moore", true, 20, 20, 5, 10);
    s1.nucleate();
    s1.runCa();
    s1.printArrays();
    s1.runMcOpt();
    s1.printArrays();
    return 0;
}