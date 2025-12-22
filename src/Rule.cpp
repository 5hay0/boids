#include "../include/Rule.hpp"


bd::Cohesion::Cohesion() {
    weight = 0.01;
}

bd::Cohesion::Cohesion(const double& w) {
    weight = w;
    if(weight < 0){
        weight = 0;
    } 
    if(weight > 1){
        weight = 1;
    }
}

Vec2<unit> bd::Cohesion::apply(const Boid& b, const Flock& f) const {
    Vec2<unit> vRes(0,0);
    int count = 0;
    DynamicArray<Boid> nei = f.getNeighbours(b);
    if(nei.getSize() == 0){
        return Vec2<unit>(0,0);
    }
    for(size_t i = 0; i < nei.getSize(); i++){
        if(nei.get(i) == b){
            continue;
        }
        Vec2<unit> vTmp = nei.get(i).getPos() - b.getPos();
        double dist2 = vTmp.getX()* vTmp.getX() + vTmp.getY()* vTmp.getY();

        if (dist2 < b.getR() * b.getR()) {
            vRes += vTmp;
            count++;
        }
    }
    if(count == 0){
        return Vec2<unit>(0,0);
    }

    vRes /= count;

    return vRes * weight;
}


bd::Separation::Separation() {
    weight = 0.05;
}

bd::Separation::Separation(const double& w){
    weight = w;
    if(weight < 0){
        weight = 0;
    } 
    if(weight > 1){
        weight = 1;
    }
}

Vec2<unit> bd::Separation::apply(const Boid& b, const Flock& f) const {
    Vec2<unit> vRes(0,0);
    int count = 0;
    DynamicArray<Boid> nei = f.getNeighbours(b);
    if(nei.getSize() == 0){
        return Vec2<unit>(0,0);
    }
    for(size_t i = 0; i < nei.getSize();i++){
        if(nei.get(i) == b){
            continue;
        }
        Vec2<unit> diff = b.getPos() - nei.get(i).getPos();
        double dist2 = diff.getX()*diff.getX() + diff.getY()*diff.getY();

        if (dist2 < b.getR() * b.getR() && dist2 > 0) {
            vRes += diff / dist2;
            count++;
        }
    }
    if(count == 0){
        return Vec2<unit>(0,0);
    }

    return vRes * weight;
}

bd::Alignment::Alignment() {
    weight = 0.125;
}

bd::Alignment::Alignment(const double& w) {
    weight = w;
    if(weight < 0){
        weight = 0;
    } 
    if(weight > 1){
        weight = 1;
    }
}

Vec2<unit> bd::Alignment::apply(const Boid& b, const Flock& f) const {
    Vec2<unit> vRes(0,0);
    int count = 0;
    DynamicArray<Boid> nei = f.getNeighbours(b);
    if(nei.getSize() == 0){
        return Vec2<unit>(0,0);
    }
    for(size_t i = 0; i < nei.getSize();i++){
        if(nei.get(i) == b){
            continue;
        }
        Vec2<unit> diff = nei.get(i).getDir() - b.getDir();
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
        return Vec2<unit>(0,0);
    }

    vRes /= count;

    return vRes * weight;
}