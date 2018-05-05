#include <iostream>
#include <string>

struct Point
{
    Point(const float x, const float y) : x{x}, y{y} {}

    float x, y; // strictly Cartesian
};
