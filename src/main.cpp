#include <iostream>

#include "desert.h"
#include "utils.h"

int main(int argc, char** argv)
{
    const auto res = core::steps("res/desert");

    std::cout << "Result is " << res << std::endl;

    return 0;
}
