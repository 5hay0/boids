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
        /**
         * Constructor by with 0 arguments
         */
        Flock();

        /**
         * Constructor with arguments
         * @param nbBoids How many Boids are in the Flock
         * @param dist Distance that Boids should keep
         * @param r Ray of perception of every Boid
         */
        Flock(const int& nbBoids, const unit& dist = 50.0, const unit& r = 50.0); //default separation and r of 50
        ~Flock();

        /**
         * Add a new Boid in the Flock
         * @param b The new Boid to add
         */
        void addBoid(const Boid& b);

        /**
         * Get all the Boids in the Flock
         * @return a DynamicArray<Boid>
         */
        DynamicArray<Boid>& getBoids();

        /**
         * Get all the neighbours of a Boid
         * @param b The Boid that want to know its neighbours
         * @return a DynamicArray<Boid> with every Boid who are in the ray of perception of b
         */
        DynamicArray<Boid> getNeighbours(const Boid& b) const;

        /**
         * Get the distance Boids in the Flock should keep between them
         * @return
         */
        unit getDistance() const;

        /**
         * Change the distance Boids in the Flock should keep between them
         * @param d The new distance that need to be equals or above 0
         */
        void addDistance(unit d);

        /**
         * Remove all Boids in the Flock
         */
        void clearBoid();

        /**
         * Get the common ray of perception of Boids inside the Flock
         * @return
         */
        unit getR() const;

        /**
         * Change the common ray of perception of Boids inside the Flock
         * @param d New ray of perception (need to be equals/above to 0)
         */
        void addR(unit d);
    };
}
#endif