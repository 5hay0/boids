#include "../src/Boid.hpp"
#include <gtest/gtest.h>

class BoidTest : public ::testing::Test {
protected:
    Vec2<unit> pos;
    Vec2<unit> dir;
    Boid b;

    virtual void SetUp() {
        pos = Vec2<unit>(5, 7);
        dir = Vec2<unit>(1, 0);
        b = Boid(pos, dir, 1, 4, 5);
    }

    virtual void TearDown() {
    }
};


TEST_F(BoidTest, update){
    Vec2<unit> vRes(6,7);
    b.update();
    ASSERT_EQ(b.getPos(),vRes);
}