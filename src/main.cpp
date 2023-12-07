#include <iostream>

#include "seeds.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto locations = core::locations("res/seeds");

    const auto lowest = core::lowestLocation(locations);

    std::cout << "The min is " << *lowest << std::endl;

    return 0;
}
