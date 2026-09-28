#include "fileHandler.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

bool isBlank(const std::string& s) {
    return s.find_first_not_of(" \t\r\n") == std::string::npos;
}

bool nextLine(std::istream& in, std::string& line, int& lineNum) {
    while (std::getline(in, line)) {
        lineNum++;
        if (!isBlank(line)) {
            return true;
        }
    }
    return false;
}

Point parsePoint(const std::string& line, int lineNum) {
    std::istringstream iss(line);
    Point p;
    std::string extra;

    if (!(iss >> p) || (iss >> extra)) {
        throw std::runtime_error("Line " + std::to_string(lineNum) +
            ": expected exactly two coordinates (x y)");
    }
    return p;
}

InputData readInputFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open input file: " + filename);
    }

    InputData data;
    std::string line;
    int lineNum = 0;

    if (!nextLine(file, line, lineNum)) {
        throw std::runtime_error("Input file is empty, expected natural number n");
    }
    std::istringstream nStream(line);
    long long n = 0;
    std::string extra;
    if (!(nStream >> n) || n <= 0 || (nStream >> extra)) {
        throw std::runtime_error("Line " + std::to_string(lineNum) +
            ": n must be a positive integer");
    }
    data.n = static_cast<std::size_t>(n);

    if (!nextLine(file, line, lineNum)) {
        throw std::runtime_error("Missing starting point x0");
    }
    data.startPoint = parsePoint(line, lineNum);

    while (nextLine(file, line, lineNum)) {
        data.basePoints.push_back(parsePoint(line, lineNum));
    }

    if (data.basePoints.empty()) {
        throw std::runtime_error("At least one base point b_1...b_k is required");
    }

    return data;
}

void writeOutputFile(const std::string& filename, std::size_t n, PointSequenceGenerator& generator) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open output file for writing: " + filename);
    }

    for (std::size_t i = 0; i < n; ++i) {
        file << generator() << '\n';
    }

    if (!file) {
        throw std::runtime_error("Error while writing to file: " + filename);
    }
}