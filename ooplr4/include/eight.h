#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Eight : public Figure<T> {
public:
    Eight() : Figure<T>(8) {} 
    
    Eight(std::initializer_list<Point<T>> lst) : Figure<T>(lst) {
        if (lst.size() != 8) {
            throw std::invalid_argument("size must be 8");
        }
    }
    
    ~Eight() = default;
    
    long double Area() { return Figure<T>::CalcArea(this->v);  }
    
    Point<T> Centr() { return Figure<T>::CalcCentr(this->v); }
};