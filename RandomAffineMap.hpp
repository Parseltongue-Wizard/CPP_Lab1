#ifndef RANDOMAFFINEMAP_HPP
#define RANDOMAFFINEMAP_HPP

#include "AffineTransform.hpp"
#include <vector>
#include <random>
#include <stdexcept>

using namespace std;

class RandomAffineMap {
private:
    vector<AffineTransform> transforms;
    mutable mt19937 gen;
    mutable uniform_int_distribution<> dist;

public:
    explicit RandomAffineMap(const vector<AffineTransform>& tfs)
        : transforms(tfs),
        gen(random_device{}()),
        dist(0, static_cast<int>(tfs.size()) - 1)
    {
        if (tfs.empty()) throw invalid_argument("Affine Transformation list empty!");
    }

    Point operator()(const Point& p) const {
        int idx = dist(gen);
        return transforms[idx](p);
    }
};

#endif
