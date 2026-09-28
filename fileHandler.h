#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include "point.h"
#include "pointSequenceGenerator.h"

struct InputData {
    std::size_t n{};
    Point startPoint{};
    std::vector<Point> basePoints;
};

InputData readInputFile(const std::string& filename);
void writeOutputFile(const std::string& filename, std::size_t n, PointSequenceGenerator& generator);