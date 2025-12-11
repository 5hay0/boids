#include "../include/Rule.hpp"
#include <gtest/gtest.h>

class RuleTest : public ::testing::Test {
    protected:
    bd::Boid center;
    bd::Boid n1, n2;
    DynamicArray<bd::Boid> neigh;

    virtual void SetUp(){
        center = bd::Boid(Vec2<double>(0,0), Vec2<double>(1,0), 1, 10, 0);

        n1 = bd::Boid(Vec2<double>(3,4), Vec2<double>(0,1), 1, 10, 0);
        n2 = bd::Boid(Vec2<double>(-2,1), Vec2<double>(0,-1), 1, 10, 0);

        neigh.add(center);
        neigh.add(n1);
        neigh.add(n2);
    }

    virtual void TearDown() {
    }
};