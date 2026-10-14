#include "polygons/polygon.hpp"

#include <cmath>
#include <utility>

namespace polygons {

Polygon::Polygon(std::vector<Point> points, std::string name)
    : points_(std::move(points)), name_(std::move(name)) {}

const std::vector<Point>& Polygon::points() const noexcept {
    return points_;
}

const std::string& Polygon::name() const noexcept {
    return name_;
}

bool Polygon::empty() const noexcept {
    return points_.empty();
}

double Polygon::area() const noexcept {
    if (points_.size() < 3) {
        return 0.0;
    }
    const Point origin = points_.front();
    long double twiceArea = 0.0L;
    for (std::size_t i = 1; i + 1 < points_.size(); ++i) {
        const long double ax = static_cast<long double>(points_[i].x) - origin.x;
        const long double ay = static_cast<long double>(points_[i].y) - origin.y;
        const long double bx = static_cast<long double>(points_[i + 1].x) - origin.x;
        const long double by = static_cast<long double>(points_[i + 1].y) - origin.y;
        twiceArea += ax * by - ay * bx;
    }
    return static_cast<double>(std::abs(twiceArea) / 2.0L);
}

} // namespace polygons
