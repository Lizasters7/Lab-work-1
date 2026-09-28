// Compiler: MSVC (Microsoft Visual Studio 2022), Standard: C++23

#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>
#include "point.h"
#include "pointSequenceGenerator.h"
#include "fileHandler.h"

int runTests() {
    int failed = 0;

    Point p;
    if (p.x != 0.0 || p.y != 0.0) {
        std::cout << "ERROR: default-constructed Point should be (0, 0)\n";
        ++failed;
    }

    Point a{ 1.0, 2.0 };
    Point b{ 1.0, 2.0 };
    Point c{ 2.0, 0.0 };
    std::equal_to<Point> isEqual;
    std::less<Point> isLess;

    if (!isEqual(a, b)) {
        std::cout << "ERROR: equal points should compare equal (a == b)\n";
        ++failed;
    }
    if (!isLess(a, c)) {
        std::cout << "ERROR: (1,2) should be less than (2,0)\n";
        ++failed;
    }

    std::mt19937_64 rng(42);
    Point start{ 0.0, 0.0 };
    std::vector<Point> bases{ {0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0} };
    PointSequenceGenerator generator(start, bases, rng);
    Point y0 = generator();
    if (y0.x != start.x || y0.y != start.y) {
        std::cout << "ERROR: first call to generator should return x0\n";
        ++failed;
    }

    std::mt19937_64 rngSingle(1);
    Point base{ 4.0, 8.0 };
    std::vector<Point> oneBase{ base };
    PointSequenceGenerator singleGen(Point{ 0.0, 0.0 }, oneBase, rngSingle);
    Point v0 = singleGen();
    Point v1 = singleGen();
    if (v1.x != (base.x + v0.x) / 2.0 || v1.y != (base.y + v0.y) / 2.0) {
        std::cout << "ERROR: next point should equal (b + z) / 2\n";
        ++failed;
    }

    bool threw = false;
    try {
        std::mt19937_64 rngEmpty(1);
        std::vector<Point> noBases;
        PointSequenceGenerator badGen(Point{ 0.0, 0.0 }, noBases, rngEmpty);
    }
    catch (const std::invalid_argument&) {
        threw = true;
    }
    if (!threw) {
        std::cout << "ERROR: empty list of base points should throw an exception\n";
        ++failed;
    }

    if (failed == 0) {
        std::cout << "All tests passed successfully.\n";
        return 0;
    }
    std::cout << failed << " test(s) failed.\n";
    return 1;
}

int main() {
    if (runTests() != 0) {
        std::cerr << "Tests failed, stopping.\n";
        return 1;
    }

    const std::string inputFile = "input.txt";
    const std::string outputFile = "output.txt";

    try {
        InputData data = readInputFile(inputFile);

        std::random_device rd;
        std::mt19937_64 rng(rd());

        PointSequenceGenerator generator(data.startPoint, std::move(data.basePoints), rng);
        writeOutputFile(outputFile, data.n, generator);

        std::cout << "Done: " << data.n << " points written to " << outputFile << "\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 2;
    }

    return 0;
}