#pragma once

#include<iostream>
#include <algorithm>

#include<array.h>

template<class T>
Array<T>::Array() : sz(0), cap(1), v(new T[cap]) {}

template<class T>
Array<T>::Array(size_t n) : sz(n), cap(n > 0 ? 4 * n : 1), v(new T[cap]) {}

template<class T>
Array<T>::Array(size_t n, T elem) : sz(n), cap(n > 0 ? 4 * n : 1), v(new T[cap]) {
    for (size_t i = 0; i < sz; ++i) {
        v[i] = elem;
    }
}

template<class T>
Array<T>::Array(const std::initializer_list<T>& lst) : sz(0), cap(1), v(new T[cap]) {
    for (const T& elem : lst) { 
        push(elem); 
    }
}

template<class T>
Array<T>::Array(const Array<T>& other) : sz(other.sz), cap(other.cap), v(new T[cap]) {
    std::copy(other.v, other.v + sz, v);
}

template<class T>
Array<T>::Array(Array<T>&& other) noexcept : sz(0), cap(0), v(nullptr) {
    std::swap(sz, other.sz);
    std::swap(cap, other.cap);
    std::swap(v, other.v);
}

template<class T>
Array<T>::~Array() { 
    delete[] v; 
}

template<class T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] v;
        sz = other.sz;
        cap = other.cap;
        v = new T[cap];
        std::copy(other.v, other.v + sz, v);
    }
    return *this;
}

template<class T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        delete[] v;
        sz = other.sz;
        cap = other.cap;
        v = other.v;
        
        other.sz = 0;
        other.cap = 0;
        other.v = nullptr;
    }
    return *this;
}

template<class T>
void Array<T>::resize(size_t newsize) {
    cap = newsize;
    auto t = new T[cap];
    std::copy(v, v + sz, t);
    delete[] v;
    v = t;
}

template<class T>
void Array<T>::push(const T& elem) {
    if (sz >= cap) {
        resize(2 * cap);
    }
    v[sz++] = elem;
}

template<class T>
void Array<T>::pop() {
    if (sz) {
        --sz;
    }
}

template<class T>
void Array<T>::erase(size_t ind) {
    for (size_t i = ind; i < sz; ++i) {
        v[i] = v[i + 1];
    }
    --sz;
}

template<class T>
void Array<T>::clear() { 
    sz = 0; 
}

template<class T>
T& Array<T>::operator[](size_t ind) { 
    return v[ind]; 
}

template<class T>
const T& Array<T>::operator[](size_t ind) const { 
    return v[ind]; 
}

template<class T>
size_t Array<T>::size() const { 
    return sz; 
}

template<class T>
size_t Array<T>::capacity() const { 
    return cap; 
}