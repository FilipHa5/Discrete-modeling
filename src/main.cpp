#include "classes.hpp"

int main(int argc,char* argv[])
{
    Simulation s1("Moore", true, 10, 10, 5, 10);
    s1.run();
    return 0;
}