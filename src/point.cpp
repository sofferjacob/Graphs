#include "point.h"

Point::Point() : index(-1), pos(-1) {}
Point::Point(int index, int pos) : index(index), pos(pos) {}

int Point::getIndex() {
    return index;
}

int Point::getPos() {
    return pos;
}

bool Point::operator <(const Point& other) {
    return pos < other.pos;
}
bool Point::operator >(const Point& other) {
    return pos < other.pos;
}