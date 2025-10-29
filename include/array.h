#pragma once

#include<initializer_list>

template<class T> 
class Array {
    size_t sz, cap;
    T* v;

public:
    Array() : sz(0), cap(1), v(new T[cap]) {}
    
    Array(size_t n) : sz(n), cap(4 * n), v(new T[cap]) {}
    
    Array(size_t n, T elem) : sz(n), cap(4 * n), v(new T[cap]) {
      for (size_t i = 0; i < sz; ++i) {
        v[i] = elem;
      }
    }
    
    Array(const std::initializer_list<T>& lst) : sz(0), cap(1), v(new T[cap]) {
      for (const T& elem : lst) { push(elem); }
    }
    
    Array(const Array& other) : sz(other.sz), cap(other.cap), v(new T[cap]) {
        std::copy(other.v, other.v + sz, v);
    }
    
    Array(Array&& other) noexcept  : sz(0), cap(0), v(nullptr) {
        std::swap(sz, other.sz);
        std::swap(cap, other.cap);
        std::swap(v, other.v);
    }
    
    ~Array() { delete[] v; }
    
    void resize(size_t newsize) {
        cap = newsize;
        auto t = new T[cap];
        std::copy(v, v + sz, t);
        delete[] v;
        v = t;
    }
    
    void push(const T& elem) {
      if (sz >= cap) {
        resize(2 * cap);
      }
      v[sz++] = elem;
    }
    
    void pop() {
      if (sz) {
        --sz;
      }
    }
    
    void erase(size_t ind) {
      for (size_t i = ind; i < sz; ++i) {
        v[i] = v[i + 1];
      }
      --sz;
    }
    
    void clear() { sz = 0; }
    
    size_t size() const { return sz; }
    
    size_t capacity() const { return cap; }
    
    T& operator[](size_t ind) { return v[ind]; }

    const T& operator[](size_t ind) const { return v[ind]; }
    
    Array& operator=(const Array& other) {
        sz = other.sz;
        cap = other.cap;
        v = new T[cap];
        std::copy(other.v, other.v + sz, v);
        return *this; 
    }
};