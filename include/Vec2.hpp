#ifndef VEC2_HPP
#define VEC2_HPP

#include <iostream>

template <typename T>
class Vec2{
    T x;
    T y;

    public:
    Vec2();
    Vec2(T,T);
    ~Vec2();
    Vec2(const Vec2&);
    bool operator!=(const Vec2&) const;
    Vec2<T>& operator=(const Vec2&);
    Vec2<T> operator+(const Vec2&) const;
    Vec2<T> operator-(const Vec2&) const;
    Vec2<T> operator-=(const Vec2&);    
    Vec2<T> operator+=(const Vec2&);
    bool operator==(const Vec2&) const;
    Vec2<T> operator/(const T&) const;
    Vec2<T> operator/=(const T&);
    Vec2<T> operator*(const T&) const;
    Vec2<T> operator*=(const T&);

    std::ostream& operator<<(std::ostream&);

    T getX() const;
    T getY() const;
    void setX(const T&);
    void setY(const T&);
};


template <typename T>
Vec2<T>::Vec2() : x(0), y(0){}

template <typename T>
Vec2<T>::Vec2(T x,T y) : x(x), y(y){}

template <typename T>
Vec2<T>::~Vec2(){}

template <typename T>
Vec2<T>::Vec2(const Vec2& v) : x(v.x), y(v.y){}


template <typename T>
bool Vec2<T>::operator!=(const Vec2& v) const{
    if(v.x != x && v.y != y){
        return true;
    } else {
        return false;
    }
}

template <typename T>
Vec2<T>& Vec2<T>::operator=(const Vec2& v) {
    if(*this != v){
        x = v.x;
        y = v.y;
    }
    return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& v) const {
    Vec2<T> vRes;

    vRes.x = x + v.x;
    vRes.y = y + v.y;

    return vRes;
}

template <typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& v) const {
    Vec2<T> vRes;

    vRes.x = x - v.x;
    vRes.y = y - v.y;

    return vRes;
}

template <typename T>
Vec2<T> Vec2<T>::operator-=(const Vec2& v) {
    *this = *this - v;

    return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator+=(const Vec2& v) {
    *this = *this + v;

    return *this;
}

template <typename T>
bool Vec2<T>::operator==(const Vec2& v) const {
    if(*this != v){
        return false;
    } else {
        return true;
    }
}

template <typename T>
Vec2<T> Vec2<T>::operator/(const T& t) const {
    Vec2<T> vRes;

    vRes.x = x / t;
    vRes.y = y / t;

    return vRes;
}

template <typename T>
Vec2<T> Vec2<T>::operator/=(const T& t) {
    *this = *this / t;

    return *this;
}

template <typename T>
Vec2<T> Vec2<T>::operator*(const T& v) const {
    Vec2<T> vRes;

    vRes.x = x * v;
    vRes.y = y * v;

    return vRes;
}

template <typename T>
Vec2<T> Vec2<T>::operator*=(const T& t){
    *this = *this * t;
    return *this;
}

template <typename T>
std::ostream& Vec2<T>::operator<<(std::ostream& os){
    os << "(" << this->x << "," << this->y << ")";
    return os;
}

template <typename T>
T Vec2<T>::getX() const {
    return x;
}

template <typename T>
T Vec2<T>::getY() const {
    return y;
}

template <typename T>
void Vec2<T>::setX(const T& e) {
    x = e;
}

template <typename T>
void Vec2<T>::setY(const T& e) {
    y = e;
}

#endif