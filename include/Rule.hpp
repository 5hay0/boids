#ifndef RULE_HPP
#define RULE_HPP

#include "Boid.hpp"
#include "Flock.hpp"

namespace bd {

    class Rule {
    protected:
        double weight;

    public:
        virtual Vec2<unit> apply(const Boid&, const Flock&) const = 0;
    };

    class Cohesion : public Rule {
    public:
        Cohesion();
        Cohesion(const double&);
        Vec2<unit> apply(const Boid&, const Flock&) const;
    };

    class Separation : public Rule {
    public:
        Separation();
        Separation(const double&);
        Vec2<unit> apply(const Boid&, const Flock&) const;
    };

    class Alignment : public Rule {
    public:
        Alignment();
        Alignment(const double&);
        Vec2<unit> apply(const Boid&, const Flock&) const;
    };
}
#endif