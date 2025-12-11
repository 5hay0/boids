#ifndef RULE_HPP
#define RULE_HPP

#include "Vec2.hpp"
#include "DynamicArray.hpp"
#include "Boid.hpp"

class Rule {
    protected:
    double weight;

    public: 
    virtual Vec2<double> apply(const Boid&, const DynamicArray<Boid>) const = 0;
};

class Cohesion : public Rule {
    public:
    Cohesion();
    Cohesion(const double&);
    Vec2<double> apply(const Boid&, const DynamicArray<Boid>) const;
};

class Separation : public Rule {
    public:
    Separation();
    Separation(const double&);
    Vec2<double> apply(const Boid&, const DynamicArray<Boid>) const;
};

class Alignment : public Rule {
    public: 
    Alignment();
    Alignment(const double&);
    Vec2<double> apply(const Boid&, const DynamicArray<Boid>) const;
};

#endif