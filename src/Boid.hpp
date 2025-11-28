#ifndef BOID_HPP
#define BOID_HPP

#include "Vec2.hpp"

typedef size_t unit;

class Boid {
    Vec2<unit> pos;
    Vec2<unit> dir;
    unit vit;
    unit vMax;
    unit r;

    public:
    Boid();
    ~Boid();
    Boid(const Boid&);
    Boid(Vec2<unit>, Vec2<unit>, unit, unit, unit);
    Boid& operator=(const Boid&);
    void update();
    void bounds(int, int);
};


#endif