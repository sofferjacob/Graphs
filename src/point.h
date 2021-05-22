#ifndef _POINT_H
#define _POINT_H

class Point {
public:
    Point();
    Point(int index, int pos);
    int getIndex();
    int getPos();
    bool operator <(const Point& other);
    bool operator >(const Point& other);
private:
    int index;
    int pos;
};

#endif