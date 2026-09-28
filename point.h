#pragma once
#include <compare>
#include <istream>
#include <ostream>

struct Point{
    double x{};
    double y{};

    auto operator<=>(const Point&) const = default;
};

std::ostream& operator<<(std::ostream& os, const Point& p);
std::istream& operator>>(std::istream& is, Point& p);