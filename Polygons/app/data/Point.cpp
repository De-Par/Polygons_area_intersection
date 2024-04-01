#include <iostream>
#include <cmath>
#include "Point.hpp"
#include "../../Constants.hpp"

Point::Point(double coordX, double coordY) {
    this->x = coordX;
    this->y = coordY;
}

Point::Point(const Point& old) {
    this->x = old.x;
    this->y = old.y;
}

bool Point::operator==(const Point& other) const {
    return (fabs(this->x - other.x) < EPS) && (fabs(this->y - other.y) < EPS);
}

bool Point::operator<(const Point &other) const {
    if (fabs(this->x - other.x) < EPS) {
        if (this->y < other.y) return true;
        return false;
    }
    if (this->x < other.x) return true;
    return false;

}

Point& Point::operator=(const Point& old) = default;

void Point::print(bool newLine) const {
    std::cout << "(" << this->x << "; " << this->y << ") ";
    if (newLine) {
        std::cout << '\n';
    }
}