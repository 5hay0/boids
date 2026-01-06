#ifndef FLOCK_HPP
#define FLOCK_HPP

#include "DynamicArray.hpp"
#include "Boid.hpp"

namespace bd {

    class Flock {
        DynamicArray<Boid> boids;
        unit distance;
        unit boid_r;

        public:
        Flock();
        Flock(const int&, const unit& = 50.0, const unit& = 50.0); //default separation and r of 50
        //Le destructeur ?
        void addBoid(const Boid&);
        DynamicArray<Boid>& getBoids();
        DynamicArray<Boid> getNeighbours(const Boid&) const;
        unit getDistance() const;
        void addDistance(unit d);

        unit getR() const;
        void addR(unit d);
    };
}
#endif