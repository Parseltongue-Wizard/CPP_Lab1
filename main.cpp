// Компiлятор: g++ 13.1 (C++20)
// Команда: g++ -std=c++20 main.cpp -o affine

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "RandomAffineMap.hpp"

using namespace std;

int main() {
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cerr << "Couldn't open file input.txt\n";
        return 1;
    }

    size_t n;
    Point start;
    fin >> n;
    if (!fin) {
        cerr << "Error reading number of points.\n";
        return 2;
    }

    fin >> start.x >> start.y;
    if (!fin) {
        cerr << "Error reading starting point.\n";
        return 3;
    }
    
    vector<AffineTransform> transforms;
    AffineTransform t;
    while (true) {
        if (!(fin >> t)) break;
        transforms.push_back(t);
    }

    if (transforms.empty()) {
        cerr << "Couldn't find any transformations.\n";
        return 5;
    }

    RandomAffineMap randomMap(transforms);

    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cerr << "Couldn't open file output.txt\n";
        return 6;
    }

    Point current = start;
    for (size_t i = 0; i < n; ++i) {
        fout << current.x << ' ' << current.y << '\n';
        current = randomMap(current);
    }

    cout << "Complete. Output saved in output.txt\n";
    return 0;
}
