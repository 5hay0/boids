#include "../include/Boid.hpp"
#include <cmath>
#include "SFML/Graphics.hpp"

bd::Boid::Boid(): pos(Vec2<unit>()), dir(Vec2<unit>()), speed(0), speedMax(1), r(0){}

bd::Boid::~Boid(){}

bd::Boid::Boid(const Boid& b) : pos(Vec2<unit>(b.pos)), dir(Vec2<unit>(b.dir)), speed(b.speed), speedMax(b.speedMax), r(b.r){}

bd::Boid::Boid(Vec2<unit> p, Vec2<unit> d, unit v, unit vM, unit ray) : pos(p), dir(d), speed(v), speedMax(vM), r(ray){
    unit rDir = std::sqrt(dir.getX() * dir.getX() + dir.getY() * dir.getY());
    if(rDir != 0){
        dir.setX(std::round((dir.getX()/rDir) * 1000.0) / 1000.0);
        dir.setY(std::round((dir.getY()/rDir) * 1000.0) / 1000.0);
    }
    if(speed < 0){
        speed = 0;
    }
    if(speedMax <= 0) {
        speedMax = 1;
    }
    if(speed > speedMax){
        speed = speedMax;
    }
}

bd::Boid& bd::Boid::operator=(const Boid& b){
    if(this != &b){
        pos = b.pos;
        dir = b.dir;
        speed = b.speed;
        speedMax = b.speedMax;
        r = b.r;
    }
    return *this;
}

void bd::Boid::update(){
    pos.setX(pos.getX() + dir.getX() * speed);
    pos.setY(pos.getY() + dir.getY() * speed);
}

void bd::Boid::bounds(int width, int height){
    if(pos.getX() > (unit)width){
        pos.setX(width);
        dir.setX(1);
    } 
    if(pos.getX() < 0){
        pos.setX(0);
        dir.setX(0);
    }
    if(pos.getY() > (unit)height){
        pos.setY(height);
        dir.setY(1);
    } 
    if(pos.getY() < 0){
        pos.setY(0);
        dir.setX(0);
    }
}

Vec2<unit> bd::Boid::getPos() const{
    return pos;
}

Vec2<unit> bd::Boid::getDir() const {
    return dir;
}

unit bd::Boid::getSpeed() const {
    return speed;
}

unit bd::Boid::getSpeedMax() const {
    return speedMax;
}

unit bd::Boid::getR() const {
    return r;
}

bool bd::Boid::operator==(const Boid& b) const {
    bool res = true;
    if(pos != b.getPos() || dir != b.getDir() || speed != b.getSpeed() || speedMax != b.getSpeedMax() || r != b.getR()){
        res = false;
    }
    return res;
}