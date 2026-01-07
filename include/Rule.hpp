#ifndef RULE_HPP
#define RULE_HPP

#include "Boid.hpp"
#include "Flock.hpp"

namespace bd {

    class Rule {
    protected:
        double weight;

    public:
        /**
         * Application of the rule on a Boid regarding a Flock
         * @return Correction of the Boid's direction
         */
        virtual Vec2<unit> apply(const Boid&, const Flock&) const = 0;

        /**
         * Add 0.01 to the weight of the rule
         * Don't go above 1
         */
        void addWeight(){if (weight + 0.01f > 1) weight = 1; else weight+= 0.01f;};
        /**
         * Remove 0.01 to the weight of the rule
         * Don't go below 0
         */
        void removeWeight(){if (weight - 0.01f<0) weight = 0; else weight-= 0.01f;};
        /**
         * Get the weight of the rule
         * @return
         */
        double getWeight(){return weight;};
        /**
         * Set the weight of the rule
         * @param f New weight, if above 1 f is forced to 1. If below 0, f is forced to 0
         */
        void setWeight(float& f){if (f > 1) weight = 1; else if (f<0) weight= 0; else weight = f;};
    };

    class Cohesion : public Rule {
    public:
        Cohesion();
        Cohesion(const double&);
        /**
         * Application of the rule of Cohesion on a Boid regarding a Flock
         * @param b The Boid
         * @param f The Flock of b
         * @return Correction of the Boid's direction
         */
        Vec2<unit> apply(const Boid& b, const Flock& f) const;
    };

    class Separation : public Rule {
    public:
        Separation();
        Separation(const double&);
        /**
         * Application of the rule of Separation on a Boid regarding a Flock
         * @param b The Boid
         * @param f The Flock of b
         * @return Correction of the Boid's direction
         */
        Vec2<unit> apply(const Boid& b, const Flock& f) const;
    };

    class Alignment : public Rule {
    public:
        Alignment();
        Alignment(const double&);
        /**
         * Application of the rule of Alignment on a Boid regarding a Flock
         * @param b The Boid
         * @param f The Flock of b
         * @return Correction of the Boid's direction
         */
        Vec2<unit> apply(const Boid& b, const Flock& f) const;
    };

    class Fuite : public Rule {
    public:
        Fuite();
        Fuite(const double&);
        /**
         * Application of the rule "Run in the opposite direction" on a Boid regarding a Flock of predators
         * Get the average direction to flee every predator near Boid
         * @param b The Boid
         * @param p The Flock of predators
         * @return Correction of the Boid's direction
         */
        Vec2<unit> apply(const Boid& b, const Flock& p) const;
    };
}
#endif