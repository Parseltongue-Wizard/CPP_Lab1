#ifndef AFFINETRANSFORM_HPP
#define AFFINETRANSFORM_HPP

#include <array>
#include <stdexcept>
#include <iostream>

using namespace std;

struct Point {
    double x{};
    double y{};
};

class AffineTransform {
private:
    array<array<double, 2>, 2> M{};
    array<double, 2> v{};

public:
    AffineTransform() = default;

    AffineTransform(double a, double b, double c, double d, double e, double f) {
        M = { {{a, b}, {c, d}} };
        v = { e, f };
    }

    Point operator()(const Point& p) const noexcept {
        Point result;
        result.x = M[0][0] * p.x + M[0][1] * p.y + v[0];
        result.y = M[1][0] * p.x + M[1][1] * p.y + v[1];
        return result;
    }

    friend istream& operator>>(istream& is, AffineTransform& t) {
        double a, b, c, d, e, f;
        if (!(is >> a >> b >> c >> d >> e >> f)) {
            is.setstate(ios::failbit);
            return is;
        }
        t = AffineTransform(a, b, c, d, e, f);
        return is;
    }
};

#endif
