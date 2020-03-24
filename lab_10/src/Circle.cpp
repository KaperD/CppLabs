#include <cstring>
#include <stdio.h>

#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y), radius(radius) {
    my_label = new char[strlen(label) + 1];
    strcpy(my_label, label);
}

Circle::~Circle() {
    delete [] my_label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, my_label);
}

bool Circle::is_inside(int dot_x, int dot_y) const {
    if ((dot_x - x)*(dot_x - x) + (dot_y - y)*(dot_y - y) <= radius*radius) {
        return true;
    }
    return false;
}

void Circle::zoom(int factor) {
    radius *= factor;
}