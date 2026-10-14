#include "polygons/geometry.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace polygons {

namespace {

long double cross(const Point& origin, const Point& a, const Point& b) {
    const long double ax = static_cast<long double>(a.x) - origin.x;
    const long double ay = static_cast<long double>(a.y) - origin.y;
    const long double bx = static_cast<long double>(b.x) - origin.x;
    const long double by = static_cast<long double>(b.y) - origin.y;
    return ax * by - ay * bx;
}

long double edgeTolerance(const Point& a, const Point& b) {
    return kGeometryEpsilon * std::hypot(static_cast<long double>(b.x) - a.x, static_cast<long double>(b.y) - a.y);
}

std::vector<Point> clip(const std::vector<Point>& subject, const std::vector<Point>& boundary) {
    std::vector<Point> output = subject;
    for (std::size_t i = 0; i < boundary.size() && !output.empty(); ++i) {
        const Point a = boundary[i];
        const Point b = boundary[(i + 1) % boundary.size()];
        const long double tolerance = edgeTolerance(a, b);
        const auto distance = [&](const Point& point) {
            const long double value = cross(a, b, point);
            return std::abs(value) <= tolerance ? 0.0L : value;
        };

        auto input = std::move(output);
        output.clear();
        output.reserve(input.size() + 1);
        Point previous = input.back();
        long double previousDistance = distance(previous);

        for (const Point& current : input) {
            const long double currentDistance = distance(current);
            const bool previousInside = previousDistance >= 0.0L;
            const bool currentInside = currentDistance >= 0.0L;

            if (previousInside != currentInside) {
                const long double t = previousDistance / (previousDistance - currentDistance);
                output.push_back({
                    static_cast<double>(previous.x + t * (static_cast<long double>(current.x) - previous.x)),
                    static_cast<double>(previous.y + t * (static_cast<long double>(current.y) - previous.y))
                });
            }
            if (currentInside) {
                output.push_back(current);
            }
            previous = current;
            previousDistance = currentDistance;
        }
    }
    return convexHull(std::move(output));
}

} // namespace

std::vector<Point> convexHull(std::vector<Point> points) {
    for (const Point& point : points) {
        if (!std::isfinite(point.x) || !std::isfinite(point.y)) {
            throw std::invalid_argument("Polygon coordinates must be finite");
        }
    }
    std::sort(points.begin(), points.end());
    points.erase(std::unique(points.begin(), points.end()), points.end());
    if (points.size() < 3) {
        return points;
    }

    std::vector<Point> hull;
    hull.reserve(points.size() * 2);
    const auto append = [&](const Point& point, std::size_t start) {
        while (hull.size() >= start + 2 && cross(hull[hull.size() - 2], hull.back(), point) <= edgeTolerance(hull[hull.size() - 2], hull.back())) {
            hull.pop_back();
        }
        hull.push_back(point);
    };
    for (const Point& point : points) {
        append(point, 0);
    }
    const std::size_t upperStart = hull.size() - 1;
    for (auto it = points.rbegin() + 1; it != points.rend(); ++it) {
        append(*it, upperStart);
    }
    hull.pop_back();
    return hull;
}

Polygon intersectPolygons(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        return {};
    }
    std::vector<std::vector<Point>> hulls;
    hulls.reserve(polygons.size());
    for (const Polygon& polygon : polygons) {
        hulls.push_back(convexHull(polygon.points()));
    }
    if (std::any_of(hulls.begin(), hulls.end(), [](const auto& hull) { return hull.size() < 3; })) {
        return {};
    }
    auto result = std::move(hulls.front());
    for (std::size_t i = 1; i < hulls.size(); ++i) {
        result = clip(result, hulls[i]);
        if (result.size() < 3) {
            return {};
        }
    }
    return Polygon(std::move(result));
}

} // namespace polygons
