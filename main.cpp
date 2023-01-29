#include "classes.hpp"

int main(int argc,char* argv[])
{
    CellularAutomata2D s1("Moore", true, 20, 20, 5);
    s1.nucleate();
    s1.runCa();
    s1.printArrays();
    return 0;
}