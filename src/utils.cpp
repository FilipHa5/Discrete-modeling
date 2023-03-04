#include <map>
#include "../include/utils.hpp"

namespace utils
{

    using namespace utils;

    int getMode(std::map<int, int> counter)
    {
        int most_common_value = 0;
        int most_common_counter = 0;
        for (auto const &p : counter)
        {
            if (p.first != 0)
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
} // utils