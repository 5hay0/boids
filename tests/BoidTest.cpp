#include "../include/Boid.hpp"
#include <gtest/gtest.h>

class BoidTest : public ::testing::Test {
protected:
    Vec2<unit> pos;
    Vec2<unit> dir;
    Boid b;

    virtual void SetUp() {
        pos = Vec2<unit>(5, 7);
        dir = Vec2<unit>(1, 1);
        b = Boid(pos, dir, 1, 4, 5);
    }

    virtual void TearDown() {
    }
};


TEST_F(BoidTest, update){
    Vec2<unit> vRes(5.707,7.707);
    b.update();
    ASSERT_EQ(b.getPos(),vRes);
}

TEST_F(BoidTest, boundsLower0){
    Vec2<unit> pos;
    Vec2<unit> dir;
    Boid b1;
    pos = Vec2<unit>(-1, -1);
    dir = Vec2<unit>(0, 1);
    b1 = Boid(pos, dir, 1, 4, 5);

    Vec2<unit> vRes(0,0);
    b1.bounds(5,5);

    ASSERT_EQ(vRes, b1.getPos());
    ASSERT_EQ(vRes, b1.getDir());
}

TEST_F(BoidTest, boundsHigherLimit){
    Vec2<unit> vResPos(4,4);
    Vec2<unit> vResDir(1,1);
    b.bounds(4,4);

    ASSERT_EQ(vResPos, b.getPos());
    ASSERT_EQ(vResDir, b.getDir());
}

TEST_F(BoidTest, operatorEqual){
    ASSERT_TRUE(pos == pos);
}