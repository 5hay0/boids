#include "../include/Rule.hpp"


Cohesion::Cohesion() {
    weight = 0.01;
    flock = new DynamicArray<Boid>(50);
}

Vec2<double> Cohesion::apply() const {
    Vec2<double> vRes(0,0);
    for(int i = 1; i < flock->getSize(); i++){
        vRes += flock->get(i).getPos() - flock->get(0).getPos();
    }
    vRes /= flock->getSize();

    return vRes;
}


Separation::Separation() {
    weight = 0.05;
    flock = new DynamicArray<Boid>(50);
}

Vec2<double> Separation::apply() const {
    Vec2<double> vRes(0,0);
    for(int i = 1; i < flock->getSize();i++){
        Vec2<double> vTmp1(flock->get(0).getPos() - flock->get(i).getPos());
        Vec2<double> vTmp2(flock->get(0).getPos() - flock->get(i).getPos());
        vTmp2.setX(std::abs(vTmp2.getX()));
        vTmp2.setY(std::abs(vTmp2.getY()));
        vRes += vTmp1 / (vTmp2 * vTmp2);
    }

    return vRes;
}

Alignment::Alignment() {
    weight = 0.125;
    flock = new DynamicArray<Boid>(50);
}

Vec2<double> Alignment::apply() const {
    Vec2<double> vRes(0,0);
    for(int i = 1; i < flock->getSize();i++){
        vRes += flock->get(i).getDir() - flock->get(0).getDir();
    }
    vRes /= flock->getSize();

    return vRes;
}