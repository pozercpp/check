#pragma once
#include <iostream>

template<class T> 
class Point {
public:
    T x, y;

    Point() : x(0), y(0) {}
    
    Point(T x_, T y_) : x(x_), y(y_) {}
    
    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x >> p.y;
        return is;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << '(' << p.x << ' ' << p.y << ')';
        return os;
    }
    
    friend bool operator==(const Point<T>& a, const Point<T>& b) { return a.x == b.x && a.y == b.y; } 
    friend bool operator!=(const Point<T>& a, const Point<T>& b) { return !(a == b); }
};