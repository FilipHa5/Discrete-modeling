#include "classes.hpp"

int MonteCarlo::calculateEnergy(int id, std::map<int, int> neighbourhood)
{
  int energy = 0;
  for (auto const &p : neighbourhood)
  {
    if (p.first != id)
      energy++;
  }

  return energy;
}