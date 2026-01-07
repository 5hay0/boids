#include "../include/Flock.hpp"

bd::Flock::Flock() : boids(), distance(50), boid_r(50) {}

bd::Flock::Flock(const int& nbBoids, const unit& d, const unit& b_r) : boids(nbBoids) {
    this->distance = d;
    this-> boid_r = b_r;
}

bd::Flock::~Flock() {}


void bd::Flock::addBoid(const Boid& b){
    boids.add(b);
}

DynamicArray<bd::Boid>& bd::Flock::getBoids() {
    return boids;
}

DynamicArray<bd::Boid> bd::Flock::getNeighbours(const Boid& b) const {
    DynamicArray<Boid> nei;

    for(size_t i = 0; i < boids.getSize(); i++){
        const Boid& other = boids.get(i);

        if(other == b){
            continue;
        }

        double dx = other.getPos().getX() - b.getPos().getX();
        double dy = other.getPos().getY() - b.getPos().getY();
        double dist2 = dx*dx + dy*dy;

        if (dist2 < b.getR() * b.getR()) {
            nei.add(other);
        }
    }

    return nei;
}

unit bd::Flock::getDistance() const {
    return this->distance;
}

void bd::Flock::addDistance(unit d) {
    if (distance+d < 51 && distance +d > 4) {
        distance += d;
    }
}

unit bd::Flock::getR() const {
    return this->boid_r;
}

void bd::Flock::addR(unit d) {
    if (((boid_r+d) < 101) && ((boid_r+d) > 9)) {
        boid_r += d;
        for (int i = 0; i< this->getBoids().getSize(); i++) {
            this->getBoids().get(i).setR(getR());
        }
    }
}

void bd::Flock::clearBoid() {
    this->getBoids().clear();
}

