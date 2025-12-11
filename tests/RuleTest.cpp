#include "../include/Rule.hpp"
#include <gtest/gtest.h>

class RuleTest : public ::testing::Test {
    protected:
    Boid center;
    Boid n1, n2;
    DynamicArray<Boid> neigh;

    virtual void SetUp(){
        center = Boid(Vec2<double>(0,0), Vec2<double>(1,0), 1, 10, 0);

        n1 = Boid(Vec2<double>(3,4), Vec2<double>(0,1), 1, 10, 0);
        n2 = Boid(Vec2<double>(-2,1), Vec2<double>(0,-1), 1, 10, 0);

        neigh.add(center);
        neigh.add(n1);
        neigh.add(n2);
    }

    virtual void TearDown() {
    }
};