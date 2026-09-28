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

/*File format:
 *   line 1:     n    - number of points to generate (a natural number)
 *   line 2:     x y  - starting point x0
 *   lines 3...: x y  - base points b1..bk (one per line, until the end of the file)*/
InputData readInputFile(const std::string& filename);
void writeOutputFile(const std::string& filename, std::size_t n, PointSequenceGenerator& generator);