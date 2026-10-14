#pragma once

namespace polygons {

struct Point {
    double x = 0.0;
    double y = 0.0;

    constexpr bool operator==(const Point& other) const noexcept {
        return x == other.x && y == other.y;
    }

    constexpr bool operator<(const Point& other) const noexcept {
        return x < other.x || (x == other.x && y < other.y);
    }
};

} // namespace polygons
