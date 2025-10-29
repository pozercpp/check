#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Six : public Figure<T> {
public:
    Six() : Figure<T>(6) {} 
    
    Six(std::initializer_list<Point<T>> lst) : Figure<T>(lst) {
        if (lst.size() != 6) {
            throw std::invalid_argument("size must be 8");
        }
    }
    
    ~Six() = default;
    
    long double Area() { return Figure<T>::CalcArea(this->v);  }
    
    Point<T> Centr() { return Figure<T>::CalcCentr(this->v); }
};