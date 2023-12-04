#include <fstream>

#include "include/core_trebuchet_calibration.h"

namespace core
{

std::vector<std::string> readInput(const char* fileName)
{
    std::vector<std::string> lines;

    std::fstream stream;
    stream.open(std::string(CMAKE_SOURCE_DIR) + "/" + fileName);

    std::string line;
    while (std::getline(stream, line))
    {
        if (!line.empty())
            lines.push_back(line);
    }

    return lines;
}

} // namespace core
