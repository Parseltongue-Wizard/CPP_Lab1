#pragma once

#include <istream>

struct Point {
    double x{};
    double y{};
};

struct Matrix2x2 {
    double m11{}, m12{}, m21{}, m22{};
};

class AffineTransform {
private:
    Matrix2x2 m;
    Point t;

public:
    AffineTransform() = default;

    AffineTransform(double a, double b, double c, double d, double e, double f) {
        m = {a, b, c, d};
        t = {e, f};
    }

    Point operator()(const Point& p) const noexcept {
        Point res;
        res.x = m.m11 * p.x + m.m12 * p.y + t.x;
        res.y = m.m21 * p.x + m.m22 * p.y + t.y;
        return res;
    }

    friend std::istream& operator>>(std::istream& is, AffineTransform& t) {
        double a, b, c, d, e, f;
        if (!(is >> a >> b >> c >> d >> e >> f)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        t = AffineTransform(a, b, c, d, e, f);
        return is;
    }
};
