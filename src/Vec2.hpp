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
};


template <typename T>
Vec2<T>::Vec2() : x(0), y(0){}

template <typename T>
Vec2<T>::Vec2(T x,T y) : x(x), y(y){}

template <typename T>
Vec2<T>::~Vec2(){}



#endif