#ifndef BOID_HPP
#define BOID_HPP

#include "Vec2.hpp"

typedef double unit;

class Boid {
    Vec2<unit> pos;
    Vec2<unit> dir;
    unit speed;
    unit speedMax;
    unit r;

    public:
    Boid();
    ~Boid();
    Boid(const Boid&);
    Boid(Vec2<unit>, Vec2<unit>, unit, unit, unit);
    Boid& operator=(const Boid&);
    void update();
    void bounds(int, int);

    Vec2<unit> getPos() const;
    Vec2<unit> getDir() const;
    unit getSpeed() const;
    unit getSpeedMax() const;
    unit getR() const;
};


#endif