#include "../src/Vec2.hpp"
#include <gtest/gtest.h>


class Vec2Test : public ::testing::Test {
protected:
    Vec2<int> v1;
    Vec2<int> v2;

    virtual void SetUp() {
        v1 = Vec2<int>(6, 8);
        v2 = Vec2<int>(1, 1);
    }

    virtual void TearDown() {
    }
};

TEST_F(Vec2Test, operatorDifference){
    ASSERT_TRUE(v1 != v2);
}

TEST_F(Vec2Test, operatorEqual){
    ASSERT_FALSE(v1 == v2);
}

TEST_F(Vec2Test, operatorPlus){
    Vec2<int> vRes(7,9);
    ASSERT_EQ(vRes, v1 + v2);
}

TEST_F(Vec2Test, operatorLess){
    Vec2<int> vRes(5,7);
    ASSERT_EQ(vRes, v1 - v2);
}

TEST_F(Vec2Test, operatorMult){
    Vec2<int> vRes(12,16);
    ASSERT_EQ(vRes, v1 * 2);
}

TEST_F(Vec2Test, operatorDiv){
    Vec2<int> vRes(3,4);
    ASSERT_EQ(vRes, v1 / 2);
}

TEST_F(Vec2Test, operatorPlusEqual){
    Vec2<int> vRes(7,9);
    v1 += v2;
    ASSERT_EQ(vRes,v1);
}

TEST_F(Vec2Test, operatorLessEqual){
    Vec2<int> vRes(5,7);
    v1 -= v2;
    ASSERT_EQ(vRes,v1);
}

TEST_F(Vec2Test, operatorMultEqual){
    Vec2<int> vRes(12,16);
    v1 *= 2;
    ASSERT_EQ(vRes,v1);
}

TEST_F(Vec2Test, operatorDivEqual){
    Vec2<int> vRes(3,4);
    v1 /= 2;
    ASSERT_EQ(vRes,v1);
}

TEST_F(Vec2Test, operatorAff){
    std::stringstream sRes;
    v1 << sRes;
    ASSERT_EQ("(6,8)", sRes.str());
}