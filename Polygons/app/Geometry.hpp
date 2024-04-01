#pragma once
#include <set>
#include "data/Polygon.hpp"

typedef std::tuple<Point, Point> LinearSegment;

class Geometry {
public:
    static double denominator(LinearSegment& seg_1, LinearSegment& seg_2);
    static double orientation(Point& previous, Point& candidate, Point& current);
    static double dist(Point& pnt_1, Point& pnt_2);
    static bool inside(Point& pnt, Polygon& pol);
    static Point* linearSegmentsIntersection(LinearSegment& seg_1, LinearSegment& seg_2);
    static Point minYPoint(std::vector<Point>& pnt_v);
    static std::vector<Point> convexHull(std::set<Point>& p_set);
    static Polygon clipPolygons(std::vector<Polygon>& pol_v);
};
