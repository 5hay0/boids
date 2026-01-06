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
    Vec2<unit> vRes(0.f,0.f);
    DynamicArray<Boid> nei = f.getNeighbours(b);

    int count = nei.getSize();

    if(count == 0){
        return vRes;
    }
    for(size_t i = 0; i < count; i++){
        Vec2<unit> vTmp = nei.get(i).getPos() - b.getPos();
        vRes += vTmp;
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

    DynamicArray<Boid> nei = f.getNeighbours(b);
    int countTotal = nei.getSize();
    int count = 0;

    if(countTotal == 0){
        return vRes;
    }
    for(size_t i = 0; i < nei.getSize();i++){
        Vec2<unit> diff = b.getPos() - nei.get(i).getPos();
        double dist2 = diff.getX()*diff.getX() + diff.getY()*diff.getY();
        double dist = sqrt(dist2);

        if (dist < f.getDistance() && dist > 0) {
            vRes += diff / dist;
            count += 1;
        }
    }
    //normalisation
    double len = sqrt(vRes.getX()*vRes.getX() + vRes.getY()*vRes.getY());

    if (count == 0) {
        // on a aucun voisin trop proche
        return vRes;
    }
    vRes /= count;
    if (len > 0) {
        vRes = vRes / len;
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

    for(size_t i = 0; i < nei.getSize(); i++){
        double dx = nei.get(i).getPos().getX() - b.getPos().getX();
        double dy = nei.get(i).getPos().getY() - b.getPos().getY();
        double dist2 = dx*dx + dy*dy;

        if (dist2 > 0 && dist2 < f.getDistance()*f.getDistance()) {
            vRes += nei.get(i).getDir();
            count++;
        }
    }

    if (count == 0)
        return Vec2<unit>(0,0);

    //moyenne
    vRes /= count;

    //normalisation
    double len = sqrt(vRes.getX()*vRes.getX() + vRes.getY()*vRes.getY());
    if (len > 0)
        vRes = vRes / len;

    return vRes * weight;
}