#pragma once

#include "Figure.hpp"

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);
    virtual ~Rectangle() = default;

    virtual void print() const;
    virtual bool is_inside(int x, int y) const;
    virtual void zoom(int factor);

protected:
    int width;
    int height;
};
