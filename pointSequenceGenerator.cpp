#include "pointSequenceGenerator.h"
#include <stdexcept>

PointSequenceGenerator::PointSequenceGenerator(Point start, std::vector<Point> basePoints_, std::mt19937_64& rng_)
    : currentPoint(start), basePoints(std::move(basePoints_)), rng(rng_), indexDist(0, validatedMaxIndex(basePoints)) {}

std::size_t PointSequenceGenerator::validatedMaxIndex(const std::vector<Point>& basePoints) {
    if (basePoints.empty()) {
        throw std::invalid_argument(
            "At least one base point b_1...b_k is required");
    }
    return basePoints.size() - 1;
}

Point PointSequenceGenerator::calculateMidpoint(const Point& b, const Point& z) {
    return Point{(b.x + z.x) / 2.0, (b.y + z.y) / 2.0};
}

Point PointSequenceGenerator::operator()() {
    Point result = currentPoint;
    const std::size_t idx = indexDist(rng);
    currentPoint = calculateMidpoint(basePoints[idx], currentPoint);
    return result;
}