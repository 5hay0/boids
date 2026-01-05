#ifndef FLOCK_HPP
#define FLOCK_HPP

#include "DynamicArray.hpp"
#include "Boid.hpp"

namespace bd {

    class Flock {
        DynamicArray<Boid> boids;

        public:
        Flock();
        Flock(const int&);
        //Le destructeur ?
        void addBoid(const Boid&);
        DynamicArray<Boid>& getBoids();
        DynamicArray<Boid> getNeighbours(const Boid&) const;
    };
}
#endif