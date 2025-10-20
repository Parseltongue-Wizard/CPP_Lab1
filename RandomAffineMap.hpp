#pragma once

#include "AffineTransform.hpp"
#include <vector>
#include <random>
#include <stdexcept>

class RandomAffineMap {
private:
    std::vector<AffineTransform> transforms;
    mutable std::mt19937 gen;
    mutable std::uniform_int_distribution<size_t> dist;

public:
    explicit RandomAffineMap(const std::vector<AffineTransform>& tfs)
        : transforms(tfs)
    {
        if (tfs.empty())
            throw std::invalid_argument("Error: transformation list cannot be empty");

        gen.seed(std::random_device{}());
        dist = std::uniform_int_distribution<size_t>(0, tfs.size() - 1);
    }

    Point operator()(const Point& p) const {
        size_t idx = dist(gen);
        return transforms[idx](p);
    }
};


