#ifndef RULE_HPP
#define RULE_HPP

#include "Vec2.hpp"
#include "DynamicArray.hpp"
#include "Boid.hpp"

class Rule {
    protected:
    double weight;
    DynamicArray<Boid>* flock;

    public: 
    virtual Vec2<double> apply() const = 0;
};

class Cohesion : public Rule {
    public:
    Cohesion();
    Vec2<double> apply() const;
};

class Separation : public Rule {
    public:
    Separation();
    Vec2<double> apply() const;
};

class Alignment : public Rule {
    public: 
    Alignment();
    Vec2<double> apply() const;
};

#endif