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
#include "tests.h"

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