#include <stdio.h>
#include <cmath>

#include "Rectangle.hpp"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

bool Rectangle::is_inside(int dot_x, int dot_y) const {
    if (abs(dot_x - x) <= width / 2 && abs(dot_y - y) <= height / 2) {
        return true;
    }
    return false;
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}