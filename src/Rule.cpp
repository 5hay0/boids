#include "../include/Rule.hpp"


Cohesion::Cohesion() {
    weight = 0.01;
}

Cohesion::Cohesion(const double& w) {
    weight = w;
    if(weight < 0){
        weight = 0;
    } 
    if(weight > 1){
        weight = 1;
    }
}

Vec2<double> Cohesion::apply(const Boid& b, const Flock& f) const {
    Vec2<double> vRes(0,0);
    int count = 0;
    DynamicArray<Boid> nei = f.getNeighbours(b);
    if(nei.getSize() == 0){
        return vRes;
    }
    for(size_t i = 0; i < nei.getSize(); i++){
        if(nei.get(i) == b){
            continue;
        }
        Vec2<double> vTmp = nei.get(i).getPos() - b.getPos();
        double dist2 = vTmp.getX()* vTmp.getX() + vTmp.getY()* vTmp.getY();

        if (dist2 < b.getR() * b.getR()) {
            vRes += vTmp;
            count++;
        }
    }
    if(count == 0){
        return Vec2<double>(0,0);
    }

    vRes /= count;

    return vRes * weight;
}


Separation::Separation() {
    weight = 0.05;
}

Separation::Separation(const double& w){
    weight = w;
    if(weight < 0){
        weight = 0;
    } 
    if(weight > 1){
        weight = 1;
    }
}

Vec2<double> Separation::apply(const Boid& b, const Flock& f) const {
    Vec2<double> vRes(0,0);
    int count = 0;
    DynamicArray<Boid> nei = f.getNeighbours(b);
    if(nei.getSize() == 0){
        return vRes;
    }
    for(size_t i = 0; i < nei.getSize();i++){
        if(nei.get(i) == b){
            continue;
        }
        Vec2<double> diff = b.getPos() - nei.get(i).getPos();
        double dist2 = diff.getX()*diff.getX() + diff.getY()*diff.getY();

        if (dist2 < b.getR() * b.getR() && dist2 > 0) {
            vRes += diff / dist2;
            count++;
        }
    }
    if(count == 0){
        return Vec2<double>(0,0);
    }

    return vRes * weight;
}

Alignment::Alignment() {
    weight = 0.125;
}

Alignment::Alignment(const double& w) {
    weight = w;
    if(weight < 0){
        weight = 0;
    } 
    if(weight > 1){
        weight = 1;
    }
}

Vec2<double> Alignment::apply(const Boid& b, const Flock& f) const {
    Vec2<double> vRes(0,0);
    int count = 0;
    DynamicArray<Boid> nei = f.getNeighbours(b);
    if(nei.getSize() == 0){
        return vRes;
    }
    for(size_t i = 0; i < nei.getSize();i++){
        if(nei.get(i) == b){
            continue;
        }
        Vec2<double> diff = nei.get(i).getDir() - b.getDir();
        double dist2 = (nei.get(i).getPos().getX() - b.getPos().getX()) *
                       (nei.get(i).getPos().getX() - b.getPos().getX()) +
                       (nei.get(i).getPos().getY() - b.getPos().getY()) *
                       (nei.get(i).getPos().getY() - b.getPos().getY());

        if (dist2 < b.getR()*b.getR()) {
            vRes += diff;
            count++;
        }
    }
    if(count == 0){
        return Vec2<double>(0,0);
    }

    vRes /= count;

    return vRes * weight;
}