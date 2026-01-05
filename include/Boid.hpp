#ifndef BOID_HPP
#define BOID_HPP

#include "../include/Vec2.hpp"

typedef float unit;

namespace bd {
    
    class Boid {
        Vec2<unit> pos;
        Vec2<unit> dir;
        unit speed;
        unit speedMax;
        unit r; //rayon de perception

        //Discuter accélération max

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
        bool operator==(const Boid&) const;
        void setPos(const Vec2<unit> &v);
        void setSpeed(const unit &s);
    };
}

#endif