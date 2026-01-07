#ifndef BOID_HPP
#define BOID_HPP

#include "../include/Vec2.hpp"

typedef float unit;

namespace bd {
    
    class Boid {
        /**
         * Position of the Boid represented by (x,y) is between 0,0 up to width,heigh of the simulation
         */
        Vec2<unit> pos;
        /**
         * Direction of the Boid represented by (x,y)
         * If x < 0 : the Boid will go to the left
         * If x > 0 : the Boid will go to the right
         * If y < 0 : the Boid will go up
         * If y > 0 : the Boid will go down
         */
        Vec2<unit> dir;
        unit speed;
        unit speedLimit = 0.1;
        unit speedMax;

        unit r; //zone of perception

        public:
        /**
         * Default constructor
         */
        Boid();

        /**
         * Destructor
         */
        ~Boid();

        /**
         *  Constructor by copy
         * @param b Boid that will serve as model
         */
        Boid(const Boid& b);

        /**
         * Constructor of Boid with paramaters
         *
         * @param pos Position (x,y) of the Boid represented by a vector
         * @param dir Direction of the Boid represented by a vector
         * @param speed Current Speed of the Boid
         * @param speedMax Limit of how fast a Boid can be
         * @param r How far the Boid can percive
         */
        Boid(Vec2<unit> pos, Vec2<unit> dir,unit speed, unit speedMax, unit r);

        /**
         * Change the Boid so it have the same values as the model
         * @param b Model that will copy the Boid
         * @return the modified Boid
         */
        Boid& operator=(const Boid& b);

        /**
         * Update the position of the Boid by following the formula :
         * position + direction * speed
         */
        void update();

        /**
         * Check if the Boid is not at a bordure of a simulation and modify the direction if that is the case
         * @param x width of the simulation
         * @param y height of the simulation
         */
        void bounds(int x, int y);

        /**
         * Get the position of the Boid
         * @return position of the Boid represented as a vector (x,y)
         */
        Vec2<unit> getPos() const;

        /**
         * Get the direction of the Boid
         * @return direction of the Boid represented as a vector (x,y)
         */
        Vec2<unit> getDir() const;

        /**
         * Get the actual speed of the Boid
         * @return
         */
        unit getSpeed() const;

        /**
         * Get how fast a Boid can move
         * @return
         */
        unit getSpeedMax() const;

        /**
         * Get the Boid's zone of perception
         * @return
         */
        unit getR() const;

        /**
         * Check if two Boids are the same
         * @return true if they are identical
         */
        bool operator==(const Boid&) const;

        /**
         * Change the position of the Boid
         * @param v new position of Boid that need to be in the range of the simulation
         */
        void setPos(const Vec2<unit> &v);

        /**
         * Change the current speed of the Boid
         * @param s new speed
         */
        void setSpeed(const unit &s);

        /**
         * Change the direction of the Boid
         * @param v new direction as a normalized vector
         */
        void setDir(const Vec2<unit> &v);

        /**
         * Change the Boid's ray of perception
         * @param newR new ray of perception that need to be equal or superior at 0
         */
        void setR(unit newR);

        /**
         * Get how much a Boid can accelerate
         * @return
         */
        unit getSpeedLimit();
    };
}

#endif