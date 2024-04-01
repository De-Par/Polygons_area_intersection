#include <iostream>
#include <cmath>
#include "Polygon.hpp"

Polygon::Polygon(const Point& p) {
    this->points.push_back(p);
}

Polygon::Polygon(const std::vector<Point>& p_vec) {
    this->points = p_vec;
}

Polygon& Polygon::operator+=(const Point& point) {
    this->points.push_back(point);
    return *this;
}

Point Polygon::operator[](int ind) {
    try {
        return this->points[ind];
    } catch(const std::exception& e) {
        std::cout << e.what() << '\n';
        throw;
    }
}

[[maybe_unused]] std::vector<Point>& Polygon::getPoints() {
    return this->points;
}

std::string Polygon::getName() const{
    return this->name;
}

void Polygon::setName(const std::string& str) {
    this->name = str;
}

int Polygon::size() const {
    return static_cast<int>(this->points.size());
}

double Polygon::area() const {
    double area = 0.0;
    size_t size = this->size();
    for (size_t i = 0; i < size; i++) {
        area += this->points[i].x * this->points[(i + 1) % size].y -
                this->points[(i + 1) % size].x * this->points[i].y;
    }
    return fabs(area) / 2;
}

void Polygon::display() const {
    std::cout << this->name << ": ";
    for (const Point& point : this->points) {
        point.print(false);
    }
    std::cout << '\n';
}
