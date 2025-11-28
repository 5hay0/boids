#include "Boid.hpp"
#include <cmath>

Boid::Boid(): pos(Vec2<unit>()), dir(Vec2<unit>()), vit(1), vMax(1), r(0){}

Boid::~Boid(){}

Boid::Boid(const Boid& b) : pos(Vec2<unit>(b.pos)), dir(Vec2<unit>(b.dir)), vit(b.vit), vMax(b.vMax), r(b.r){}

Boid::Boid(Vec2<unit> p, Vec2<unit> d, unit v, unit vM, unit ray) : pos(p), dir(d), vit(v), vMax(vM), r(ray){
    unit rDir = std::sqrt(dir.getX() * dir.getX() + dir.getY() * dir.getY());
    if(rDir != 0){
        dir.setX(dir.getX()/rDir);
        dir.setY(dir.getY()/rDir);
    }
    if(vit > vMax){
        vit = vMax;
    }
}

Boid& Boid::operator=(const Boid& b){
    if(this != &b){
        pos = b.pos;
        dir = b.dir;
        vit = b.vit;
        vMax = b.vMax;
        r = b.r;
    }
    return *this;
}

void Boid::update(){
    pos.setX(pos.getX() + dir.getX() * vit);
    pos.setY(pos.getY() + dir.getY() * vit);
}

void Boid::bounds(int width, int height){
    if(pos.getX() >= width){
        pos.setX(0);
    } 
    if(pos.getX() < 0){
        pos.setX(width-1);
    }
    if(pos.getY() >= height){
        pos.setY(0);
    } 
    if(pos.getY() < 0){
        pos.setY(height-1);
    }
}