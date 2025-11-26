#ifndef VEC2_HPP
#define VEC2_HPP

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
    bool operator==(const Vec2& v) const;
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

#endif