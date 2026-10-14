#pragma once

#include "polygons/polygon.hpp"

namespace polygons {

inline constexpr double kGeometryEpsilon = 1e-9;

[[nodiscard]] std::vector<Point> convexHull(std::vector<Point> points);

[[nodiscard]] Polygon intersectPolygons(const std::vector<Polygon>& polygons);

} // namespace polygons
