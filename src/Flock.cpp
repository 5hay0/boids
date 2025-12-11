#include "../include/Flock.hpp"

Flock::Flock() {}

Flock::Flock(const int& nbBoids) : boids(nbBoids) {}

void Flock::addBoid(const Boid& b){
    boids.add(b);
}

DynamicArray<Boid>& Flock::getBoids() {
    return boids;
}

DynamicArray<Boid>& Flock::getNeighbours(const Boid& b) const {
    DynamicArray<Boid> nei;

    for(size_t i = 0; i < boids.getSize(); i++){
        if(nei.get(i) == b){
            continue;
        }

        double dx = boids.get(i).getPos().getX() - b.getPos().getX();
        double dy = boids.get(i).getPos().getY() - b.getPos().getY();
        double dist2 = dx*dx + dy*dy;

        if (dist2 < b.getR() * b.getR()) {
            nei.add(boids.get(i));
        }
    }

    return nei;
}