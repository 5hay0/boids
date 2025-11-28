#include "Boid.hpp"
#include <cmath>
#include "SFML/Graphics.hpp"

Boid::Boid(): pos(Vec2<unit>()), dir(Vec2<unit>()), speed(1), speedMax(1), r(0){}

Boid::~Boid(){}

Boid::Boid(const Boid& b) : pos(Vec2<unit>(b.pos)), dir(Vec2<unit>(b.dir)), speed(b.speed), speedMax(b.speedMax), r(b.r){}

Boid::Boid(Vec2<unit> p, Vec2<unit> d, unit v, unit vM, unit ray) : pos(p), dir(d), speed(v), speedMax(vM), r(ray){
    unit rDir = std::sqrt(dir.getX() * dir.getX() + dir.getY() * dir.getY());
    if(rDir != 0){
        dir.setX(dir.getX()/rDir);
        dir.setY(dir.getY()/rDir);
    }
    if(speed > speedMax){
        speed = speedMax;
    }
}

Boid& Boid::operator=(const Boid& b){
    if(this != &b){
        pos = b.pos;
        dir = b.dir;
        speed = b.speed;
        speedMax = b.speedMax;
        r = b.r;
    }
    return *this;
}

void Boid::update(){
    pos.setX(pos.getX() + dir.getX() * speed);
    pos.setY(pos.getY() + dir.getY() * speed);
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

Vec2<unit> Boid::getPos() const{
    return pos;
}

Vec2<unit> Boid::getDir() const {
    return dir;
}

unit Boid::getSpeed() const {
    return speed;
}

unit Boid::getSpeedMax() const {
    return speedMax;
}

unit Boid::getR() const {
    return r;
}