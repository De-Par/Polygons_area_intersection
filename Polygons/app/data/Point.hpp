#pragma once

class Point {
public:
    double x, y;

    Point() : x(0), y(0) {}
    Point(double coordX, double coordY);
    Point(const Point& old);

    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;
    Point& operator=(const Point& old);

    [[maybe_unused]] void print(bool newLine = true) const;
};