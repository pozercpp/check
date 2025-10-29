#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Five : public Figure<T> {
public:
    Five() : Figure<T>(5) {}
    
    Five(std::initializer_list<Point<T>> lst) : Figure<T>(lst) {
        if (lst.size() != 5) {
            throw std::invalid_argument("size must be 5");
        }
    }
    
    ~Five() = default;
    
    long double Area() { return Figure<T>::CalcArea(this->v);  }
    
    Point<T> Centr() { return Figure<T>::CalcCentr(this->v); }
};