#include <cmath>
#include <iostream>
#include "Geometry.hpp"
#include "../Constants.hpp"

double Geometry::denominator(LinearSegment& seg_1, LinearSegment& seg_2) {
    return (std::get<1>(seg_2).y - std::get<0>(seg_2).y) *
           (std::get<1>(seg_1).x - std::get<0>(seg_1).x) -
           (std::get<1>(seg_2).x - std::get<0>(seg_2).x) *
           (std::get<1>(seg_1).y - std::get<0>(seg_1).y);
}

Point* Geometry::linearSegmentsIntersection(LinearSegment& seg_1, LinearSegment& seg_2) {
    if ((fabs(std::get<0>(seg_1).x - std::get<1>(seg_1).x) < EPS &&
        fabs(std::get<0>(seg_1).y - std::get<1>(seg_1).y) < EPS) ||
        (fabs(std::get<0>(seg_2).x - std::get<1>(seg_2).x) < EPS ||
        fabs(std::get<0>(seg_2).y - std::get<1>(seg_2).y) < EPS)) {
        return nullptr;
    }
    double dnm = denominator(seg_1, seg_2);
    if (fabs(dnm) < EPS) {
        return nullptr;
    }
    double u1 = ((std::get<1>(seg_2).x - std::get<0>(seg_2).x) *
                 (std::get<0>(seg_1).y - std::get<0>(seg_2).y) -
                 (std::get<1>(seg_2).y - std::get<0>(seg_2).y) *
                 (std::get<0>(seg_1).x - std::get<0>(seg_2).x)) / dnm;

    double u2 = ((std::get<1>(seg_1).x - std::get<0>(seg_1).x) *
                 (std::get<0>(seg_1).y - std::get<0>(seg_2).y) -
                 (std::get<1>(seg_1).y - std::get<0>(seg_1).y) *
                 (std::get<0>(seg_1).x - std::get<0>(seg_2).x)) / dnm;

    if (u1 < 0 || u1 > 1 || u2 < 0 || u2 > 1) {
        return nullptr;
    }
    double x = std::get<0>(seg_1).x + u1 * (std::get<1>(seg_1).x - std::get<0>(seg_1).x);
    double y = std::get<0>(seg_1).y + u1 * (std::get<1>(seg_1).y - std::get<0>(seg_1).y);

    return new Point(x, y);
}

bool Geometry::inside(Point& pnt, Polygon& pol) {
    bool is_inside = false;
    auto points = pol.getPoints();
    size_t j = points.size() - 1;

    for (size_t i = 0; i < points.size(); ++i) {
        double xi = points[i].x, yi = points[i].y;
        double xj = points[j].x, yj = points[j].y;
        bool intersect = ((yi > pnt.y) != (yj > pnt.y)) &&
                (pnt.x < (xj - xi) * (pnt.y - yi) / (yj - yi) + xi);
        if (intersect) {
            is_inside = !is_inside;
        }
        j = i;
    }
    return is_inside;
}

Point Geometry::minYPoint(std::vector<Point>& pnt_v) {
    Point cur_p(pnt_v[0].x, pnt_v[0].y);
    for (size_t i = 1; i < pnt_v.size(); ++i) {
        if (pnt_v[i].y < cur_p.y || (fabs(pnt_v[i].y - cur_p.y) < EPS && pnt_v[i].x < cur_p.x)) {
            cur_p.x = pnt_v[i].x;
            cur_p.y = pnt_v[i].y;
        }
    }
    return cur_p;
}

double Geometry::orientation(Point& previous, Point& candidate, Point& current) {
    return (candidate.y - previous.y) * (current.x - candidate.x) -
           (candidate.x - previous.x) * (current.y - candidate.y);
}

double Geometry::dist(Point& pnt_1, Point& pnt_2) {
    return sqrt(pow(pnt_2.x - pnt_1.x, 2) + pow(pnt_2.y - pnt_1.y, 2));
}

std::vector<Point> Geometry::convexHull(std::set<Point>& p_set) {
    auto pnt_v = std::vector<Point>(p_set.begin(), p_set.end());
    if (pnt_v.size() < MIN_POINT_AMOUNT) {
        return pnt_v;
    }
    Point src_p = minYPoint(pnt_v);
    std::vector<Point> hull;
    hull.push_back(src_p);
    Point prev_p = src_p;

    while (true) {
        Point* cp = nullptr;
        for (Point &curr_p : pnt_v) {
            if (curr_p == prev_p) {
                continue;
            }
            if (!cp) {
                cp = new Point(curr_p.x, curr_p.y);
                continue;
            }
            double area_sign = orientation(prev_p, *cp, curr_p);
            if (area_sign < 0 || (area_sign < EPS && dist(prev_p, *cp) < dist(prev_p, curr_p))) {
                *cp = curr_p;
            }
        }
        if (cp) {
            if (*cp == src_p) {
                break;
            }
            hull.push_back(*cp);
            prev_p = *cp;
        }
    }
    return hull;
}

Polygon Geometry::clipPolygons(std::vector<Polygon>& pol_v) {
    while (pol_v.size() > SINGLE) {
        Polygon pol_1(pol_v.back());
        pol_v.pop_back();
        Polygon pol_2(pol_v.back());
        pol_v.pop_back();
        std::set<Point> unique_points{};

        for (Point& p : pol_1.getPoints()) {
            if (Geometry::inside(p, pol_2)) {
                unique_points.insert(p);
            }
        }
        for (Point& p : pol_2.getPoints()) {
            if (Geometry::inside(p, pol_1)) {
                unique_points.insert(p);
            }
        }
        for (Point& p1 : pol_1.getPoints()) {
            for (Point& p2 : pol_2.getPoints()) {
                if (Geometry::dist(p1, p2) < EPS) {
                    unique_points.insert(p1);
                }
            }
        }
        for (int i = 0; i < pol_1.size(); ++i) {
            for (int j = 0; j < pol_2.size(); ++j) {
                LinearSegment seg_1(pol_1[i], pol_1[(i + 1) % pol_1.size()]);
                LinearSegment seg_2(pol_2[j], pol_2[(j + 1) % pol_2.size()]);
                Point* intersect_point = Geometry::linearSegmentsIntersection(seg_1, seg_2);
                if (intersect_point != nullptr) {
                    unique_points.insert(*intersect_point);
                }
            }
        }
        if (unique_points.empty()) {
            return {};
        }
        Polygon new_polygon(Geometry::convexHull(unique_points));
        pol_v.emplace_back(new_polygon);
        unique_points.clear();
    }
    return pol_v.back();
}