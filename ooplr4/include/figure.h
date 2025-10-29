#pragma once

#include<iostream>
#include <sstream>
#include<initializer_list>
#include<cmath>

#include<array.h>
#include<point.h>

template<class T> class Figure {
public:
    long double Area() { return CalcArea(v); }
    Point<T> Centr() { return CalcCentr(v); }

    Figure(size_t n) : v(n) {}
    Figure(const std::initializer_list<Point<T>>& lst) : v(lst) {}

    friend bool operator==(const Figure<T>& a, const Figure<T>& b) {
        if (a.v.size() != b.v.size()) { return false; }
        for (int i = 0; i < a.v.size(); ++i) {
            if (a.v[i] != b.v[i]) {
                return false;
            }
        }
        return true;
    }
    
    friend bool operator!=(const Figure<T>& a, const Figure<T>& b) { return !(a == b); }

    friend std::istream& operator>>(std::istream& is, Figure<T>& f) {
        f.ReadPoints(is);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, Figure<T>& f) {
        f.PrintPoints(os);
        return os;
    }

    void ReadPoints(std::istream& is) {
        std::string line;
        std::getline(is, line);
        std::istringstream iss(line);
        for (size_t i = 0; i < v.size(); ++i) {
            if (!(iss >> v[i].x >> v[i].y)) {
                throw std::runtime_error("Not enough coordinates");
            }
        }
    }
    
    void PrintPoints(std::ostream& os) {
        for (size_t i = 0; i < v.size(); ++i) {
            os << "( " << v[i].x << ", " << v[i].y << ")";
        }
    }

protected:
    Array<Point<T>> v;

    long double CalcArea(const Array<Point<T>>& t) const {
        long double res{0.0};
        for (int i = 0; i + 1 < t.size(); ++i) {
            res += t[i].x * static_cast<long double>(t[i + 1].y);
            res -= t[i + 1].x * static_cast<long double>(t[i].y);
        }
        res += static_cast<long double>(t[t.size() - 1].x) * static_cast<long double>(t[0].y);
        res -= static_cast<long double>(t[0].x) * static_cast<long double>(t[t.size() - 1].y);
        return std::abs(res / 2.0);
    }
    
    Point<T> CalcCentr(const Array<Point<T>>& t) const {
        T x{0}, y{0};
        for (int i = 0; i < t.size(); ++i) {
            x += t[i].x;
            y += t[i].y;
        }
        return Point<T>(x / t.size(), y / t.size());
    }
};