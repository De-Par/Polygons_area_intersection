#pragma once

#include "polygons/point.hpp"

#include <string>
#include <vector>

namespace polygons {

class Polygon {
public:
    Polygon() = default;

    explicit Polygon(std::vector<Point> points, std::string name = {});

    [[nodiscard]] const std::vector<Point>& points() const noexcept;

    [[nodiscard]] const std::string& name() const noexcept;

    [[nodiscard]] bool empty() const noexcept;

    [[nodiscard]] double area() const noexcept;

private:
    std::vector<Point> points_;
    std::string name_;
};

} // namespace polygons
