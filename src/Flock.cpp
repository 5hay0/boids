#include "../include/Flock.hpp"

bd::Flock::Flock() : boids() {}

bd::Flock::Flock(const int& nbBoids) : boids(nbBoids) {}

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
            //other.getPos()<<(std::cout<<"getNeighbours, other pos:");
            nei.add(other);
        }
    }

    return nei;
}