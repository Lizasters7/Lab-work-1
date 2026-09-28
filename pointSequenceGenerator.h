#pragma once
#include <random>
#include "point.h"
#include <vector>

class PointSequenceGenerator {
public:
    PointSequenceGenerator(Point start, std::vector<Point> basePoints_, std::mt19937_64& rng_);
    Point operator()();
private:
    Point currentPoint;
    std::vector<Point> basePoints;
    std::mt19937_64& rng;
    std::uniform_int_distribution<std::size_t> indexDist;

    static Point calculateMidpoint(const Point& b, const Point& z);
    static std::size_t validatedMaxIndex(const std::vector<Point>& basePoints);
};