// Compiler: g++ 13.1 (C++20)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "RandomAffineMap.hpp"

struct InputData {
    size_t n{};
    Point start{};
    std::vector<AffineTransform> transforms;
};

InputData parseInput(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open())
        throw std::runtime_error("Error: cannot open file " + filename);

    InputData data;

    if (!(fin >> data.n) || data.n == 0)
        throw std::runtime_error("Error: invalid number of points (n)");

    if (!(fin >> data.start.x >> data.start.y))
        throw std::runtime_error("Error: invalid starting point");

    AffineTransform t;
    size_t lineNumber = 3;
    while (fin >> t) {
        data.transforms.push_back(t);
        lineNumber++;
    }

    if (data.transforms.empty())
        throw std::runtime_error("Error: no affine transformations found");

    return data;
}

int main() {
    try {
        InputData input = parseInput("input.txt");

        RandomAffineMap randomMap(input.transforms);

        std::ofstream fout("output.txt");
        if (!fout.is_open())
            throw std::runtime_error("Error: cannot create output.txt");

        fout << std::fixed << std::setprecision(6);

        Point current = input.start;
        for (size_t i = 0; i < input.n; ++i) {
            fout << current.x << ' ' << current.y << '\n';
            current = randomMap(current);
        }
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    return 0;
}
