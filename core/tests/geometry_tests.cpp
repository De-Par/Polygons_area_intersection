#include "polygons/geometry.hpp"

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>

using polygons::convexHull;
using polygons::intersectPolygons;
using polygons::Point;
using polygons::Polygon;

namespace {

void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void near(double actual, double expected, double tolerance = 1e-8) {
    require(std::isfinite(actual) && std::abs(actual - expected) <= tolerance,
            "Expected " + std::to_string(expected) + ", got " + std::to_string(actual));
}

Polygon rectangle(double x1, double y1, double x2, double y2) {
    return Polygon({{x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}});
}

void invalidInput(const std::function<void()>& action) {
    bool thrown = false;
    try {
        action();
    } catch (const std::invalid_argument&) {
        thrown = true;
    }
    require(thrown, "Nonfinite coordinates must be rejected");
}

} // namespace

int main() {
    const std::vector<std::pair<std::string, std::function<void()>>> cases{
        {"empty and degenerate area",
         [] {
             near(Polygon().area(), 0);
             near(Polygon({{1, 2}}).area(), 0);
             near(Polygon({{1, 2}, {3, 4}}).area(), 0);
             near(Polygon({{0, 0}, {1, 1}, {2, 2}}).area(), 0);
         }},
        {"area is independent of winding",
         [] {
             const Polygon square = rectangle(-2, -2, 2, 2);
             auto reversed = square.points();
             std::reverse(reversed.begin(), reversed.end());
             near(square.area(), 16);
             near(Polygon(reversed).area(), 16);
         }},
        {"small shapes far from the origin",
         [] {
             near(rectangle(1e9, 1e9, 1e9 + 1, 1e9 + 1).area(), 1);
             near(intersectPolygons({rectangle(1e9, 1e9, 1e9 + 2, 1e9 + 2),
                                     rectangle(1e9 + 1, 1e9 + 1, 1e9 + 3, 1e9 + 3)})
                      .area(),
                  1);
         }},
        {"hull handles empty, repeated and collinear points",
         [] {
             require(convexHull({}).empty(), "Empty hull");
             require(convexHull({{1, 1}, {1, 1}}).size() == 1, "Repeated points");
             require(convexHull({{2, 2}, {0, 0}, {1, 1}, {0, 0}}) ==
                         std::vector<Point>{{0, 0}, {2, 2}},
                     "Collinear extremes");
         }},
        {"hull removes interior and edge points",
         [] {
             const auto hull =
                 convexHull({{2, 2}, {0, 0}, {1, 1}, {2, 0}, {0, 2}, {1, 0}, {0, 0}, {0, 1}});
             require(hull == std::vector<Point>{{0, 0}, {2, 0}, {2, 2}, {0, 2}},
                     "Expected a counterclockwise square without duplicates");
         }},
        {"point ordering is strict near the tolerance",
         [] {
             const Point a{0, 2};
             const Point b{0.5e-9, 1};
             const Point c{1e-9, 0};
             require(a < b && b < c && a < c, "Ordering must be transitive");
             require(!(a == b), "Equality must be exact");
         }},
        {"no polygons and degenerate polygons",
         [] {
             require(intersectPolygons({}).empty(), "Empty input");
             require(intersectPolygons({Polygon({{0, 0}, {1, 1}, {2, 2}})}).empty(), "Line");
             require(intersectPolygons({rectangle(0, 0, 2, 2), Polygon()}).empty(),
                     "Empty operand");
         }},
        {"one polygon returns its convex hull",
         [] {
             const Polygon cloud({{2, 2}, {0, 0}, {1, 1}, {0, 2}, {2, 0}}, "cloud");
             near(intersectPolygons({cloud}).area(), 4);
             require(intersectPolygons({cloud}).points().size() == 4, "Only hull vertices remain");
         }},
        {"horizontal and vertical edges intersect",
         [] { near(intersectPolygons({rectangle(0, 0, 2, 2), rectangle(1, 1, 3, 3)}).area(), 1); }},
        {"identical and contained polygons",
         [] {
             near(intersectPolygons({rectangle(0, 0, 4, 4), rectangle(0, 0, 4, 4)}).area(), 16);
             near(intersectPolygons({rectangle(0, 0, 4, 4), rectangle(1, 1, 2, 2)}).area(), 1);
         }},
        {"disjoint, touching edge and touching vertex",
         [] {
             const Polygon square = rectangle(0, 0, 2, 2);
             for (const Polygon& other :
                  {rectangle(3, 0, 4, 1), rectangle(2, 0, 3, 2), rectangle(2, 2, 4, 4)}) {
                 require(intersectPolygons({square, other}).empty(), "No two-dimensional overlap");
             }
         }},
        {"partial overlap with collinear boundaries",
         [] { near(intersectPolygons({rectangle(0, 0, 4, 2), rectangle(2, 0, 6, 2)}).area(), 4); }},
        {"diagonal clipping",
         [] {
             near(intersectPolygons({Polygon({{0, 0}, {4, 0}, {0, 4}}), rectangle(1, 1, 3, 3)})
                      .area(),
                  2);
             const Polygon diamond({{0, -1.5}, {1.5, 0}, {0, 1.5}, {-1.5, 0}});
             const Polygon overlap = intersectPolygons({diamond, rectangle(-1, -1, 1, 1)});
             near(overlap.area(), 3.5);
             require(overlap.points().size() == 8, "Expected an octagon");
         }},
        {"unordered and clockwise input",
         [] {
             const Polygon unordered({{0, 2}, {2, 0}, {2, 2}, {0, 0}, {1, 1}});
             const Polygon clockwise({{1, 1}, {1, 3}, {3, 3}, {3, 1}});
             near(intersectPolygons({unordered, clockwise}).area(), 1);
         }},
        {"multiple polygons and input immutability",
         [] {
             const std::vector<Polygon> input{Polygon(rectangle(0, 0, 5, 5).points(), "first"),
                                              rectangle(1, 1, 6, 6), rectangle(2, 2, 4, 4)};
             const auto before = input.front().points();
             near(intersectPolygons(input).area(), 4);
             require(input.size() == 3 && input.front().points() == before &&
                         input.front().name() == "first",
                     "Inputs must remain unchanged");
         }},
        {"four-triangle demo",
         [] {
             near(intersectPolygons(
                      {Polygon({{16, 0}, {0, 0}, {8, 16}}), Polygon({{16, 16}, {8, 0}, {0, 16}}),
                       Polygon({{0, 0}, {0, 16}, {16, 8}}), Polygon({{16, 16}, {16, 0}, {0, 8}})})
                      .area(),
                  128.0 / 3.0);
         }},
        {"small-scale geometry",
         [] {
             near(
                 intersectPolygons({rectangle(0, 0, 2e-6, 2e-6), rectangle(1e-6, 1e-6, 3e-6, 3e-6)})
                     .area(),
                 1e-12, 1e-20);
         }},
        {"nearly parallel edges",
         [] {
             const Polygon trapezoid({{0, 0}, {10, 1e-7}, {10, 2}, {0, 2}});
             near(intersectPolygons({trapezoid, rectangle(2, 1, 8, 3)}).area(), 6);
         }},
        {"nonfinite coordinates are rejected",
         [] {
             const double infinity = std::numeric_limits<double>::infinity();
             const double nan = std::numeric_limits<double>::quiet_NaN();
             invalidInput([&] { (void)convexHull({{infinity, 0}}); });
             invalidInput([&] { (void)convexHull({{0, nan}}); });
             invalidInput([&] { (void)intersectPolygons({Polygon(), Polygon({{nan, 0}})}); });
         }},
        {"concave contour area differs from its convex hull",
         [] {
             const Polygon contour({{0, 0}, {3, 0}, {3, 1}, {1, 1}, {1, 3}, {0, 3}});
             near(contour.area(), 5);
             near(intersectPolygons({contour}).area(), 7);
         }},
        {"closed rings and repeated boundary vertices are normalized",
         [] {
             const Polygon closed({{0, 0}, {2, 0}, {2, 2}, {2, 2}, {0, 2}, {0, 0}}, "closed");
             near(closed.area(), 4);
             const Polygon other(rectangle(0, 0, 2, 2).points(), "other");
             const Polygon result = intersectPolygons({closed, other});
             require(result.points() == std::vector<Point>{{0, 0}, {2, 0}, {2, 2}, {0, 2}},
                     "Result must be an open, canonical ring");
             require(result.name().empty(), "Intersection must not inherit an operand's name");
         }},
        {"pairwise overlaps do not imply a common overlap",
         [] {
             const Polygon a = rectangle(-3, -3, 0, 3);
             const Polygon b = rectangle(-3, -3, 3, 0);
             const Polygon c({{-2, 3}, {3, -2}, {3, 3}});
             require(intersectPolygons({a, b}).area() > 0 && intersectPolygons({a, c}).area() > 0 &&
                         intersectPolygons({b, c}).area() > 0,
                     "Every pair should overlap");
             require(intersectPolygons({a, b, c}).empty(), "No point is inside all three");
         }},
        {"three-way intersection is invariant under operand permutation",
         [] {
             const std::vector<Polygon> shapes{rectangle(0, 0, 4, 4), rectangle(1, -1, 5, 3),
                                               Polygon({{0, 0}, {6, 0}, {0, 6}})};
             std::vector<std::size_t> order{0, 1, 2};
             do {
                 // A 3×3 rectangle loses a right triangle with legs of length one.
                 near(intersectPolygons({shapes[order[0]], shapes[order[1]], shapes[order[2]]})
                          .area(),
                      8.5);
             } while (std::next_permutation(order.begin(), order.end()));
         }},
        {"hull is invariant under point permutation and leaves input untouched",
         [] {
             const std::vector<Point> expected{{-2, -2}, {2, -2}, {2, 2}, {-2, 2}};
             std::vector<Point> cloud = expected;
             cloud.insert(cloud.end(), {{0, 0}, {1, 1}, {-2, 0}, {2, 2}, {0, -2}});
             std::mt19937 generator(123);
             for (int i = 0; i < 100; ++i) {
                 std::shuffle(cloud.begin(), cloud.end(), generator);
                 const auto before = cloud;
                 require(convexHull(cloud) == expected, "Hull must have canonical vertex order");
                 require(cloud == before, "Hull construction must not reorder the source");
             }
         }},
        {"rotation translation and uniform scaling preserve intersection area",
         [] {
             const std::vector<Polygon> shapes{rectangle(-1, -1, 1, 1),
                                               Polygon({{0, -1.5}, {1.5, 0}, {0, 1.5}, {-1.5, 0}})};
             for (double angle : {0.0, 0.37, 1.2}) {
                 for (double scale : {0.125, 1.0, 16.0}) {
                     std::vector<Polygon> transformed;
                     for (const Polygon& shape : shapes) {
                         std::vector<Point> points;
                         for (const Point& point : shape.points()) {
                             points.push_back(
                                 {scale * (point.x * std::cos(angle) - point.y * std::sin(angle)) +
                                      123,
                                  scale * (point.x * std::sin(angle) + point.y * std::cos(angle)) -
                                      57});
                         }
                         transformed.emplace_back(std::move(points));
                     }
                     near(intersectPolygons(transformed).area(), 3.5 * scale * scale);
                 }
             }
         }},
        {"thin overlaps above tolerance remain visible to geometry",
         [] {
             near(intersectPolygons({rectangle(0, 0, 1, 1), rectangle(1 - 1e-8, 0, 2, 1)}).area(),
                  1e-8, 1e-15);
             require(
                 intersectPolygons({rectangle(0, 0, 1, 1), rectangle(1 + 2e-9, 0, 2, 1)}).empty(),
                 "A gap larger than the tolerance must remain disjoint");
         }},
        {"invalid operands are rejected after an already disjoint pair",
         [] {
             const double infinity = std::numeric_limits<double>::infinity();
             invalidInput([&] {
                 (void)intersectPolygons({rectangle(0, 0, 1, 1), rectangle(2, 2, 3, 3),
                                          Polygon({{0, 0}, {1, 0}, {0, -infinity}})});
             });
         }},
        {"1000 random rectangle intersections against analytical area",
         [] {
             std::mt19937 generator(42);
             std::uniform_real_distribution<double> coordinate(-100, 100);
             for (int i = 0; i < 1000; ++i) {
                 double a = coordinate(generator), b = coordinate(generator);
                 double c = coordinate(generator), d = coordinate(generator);
                 double e = coordinate(generator), f = coordinate(generator);
                 double g = coordinate(generator), h = coordinate(generator);
                 if (a > b)
                     std::swap(a, b);
                 if (c > d)
                     std::swap(c, d);
                 if (e > f)
                     std::swap(e, f);
                 if (g > h)
                     std::swap(g, h);
                 const double expected = std::max(0.0, std::min(b, f) - std::max(a, e)) *
                                         std::max(0.0, std::min(d, h) - std::max(c, g));
                 near(intersectPolygons({rectangle(a, c, b, d), rectangle(e, g, f, h)}).area(),
                      expected);
             }
         }},
        {"random convex intersections preserve symmetry and area bounds", [] {
             std::mt19937 generator(2024);
             std::uniform_real_distribution<double> coordinate(-10, 10);
             for (int i = 0; i < 200; ++i) {
                 std::vector<Point> first, second;
                 for (int j = 0; j < 12; ++j) {
                     first.push_back({coordinate(generator), coordinate(generator)});
                     second.push_back({coordinate(generator), coordinate(generator)});
                 }
                 const Polygon a(convexHull(first)), b(convexHull(second));
                 const double area = intersectPolygons({a, b}).area();
                 near(area, intersectPolygons({b, a}).area());
                 near(a.area(), intersectPolygons({a, a}).area());
                 require(area <= std::min(a.area(), b.area()) + 1e-8,
                         "Intersection cannot exceed an operand");
             }
         }}};

    int failures = 0;
    for (const auto& [name, test] : cases) {
        try {
            test();
            std::cout << "PASS " << name << '\n';
        } catch (const std::exception& error) {
            ++failures;
            std::cerr << "FAIL " << name << ": " << error.what() << '\n';
        }
    }
    std::cout << cases.size() - static_cast<std::size_t>(failures) << '/' << cases.size()
              << " geometry cases passed\n";
    return failures == 0 ? 0 : 1;
}
