#include "../include/Flock.hpp"

Flock::Flock() : boids() {}

Flock::Flock(const int& nbBoids) : boids(nbBoids) {}

void Flock::addBoid(const Boid& b){
    boids.add(b);
}

DynamicArray<Boid>& Flock::getBoids() {
    return boids;
}

DynamicArray<Boid> Flock::getNeighbours(const Boid& b) const {
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