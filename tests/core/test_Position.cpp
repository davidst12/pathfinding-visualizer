#include <gtest/gtest.h>
#include "Pathfinding/core/Position.hpp"

TEST(PositionTest, TestEqualOperator) {
    Position pos1(1, 2);
    Position pos2(1, 2);
    Position pos3(2, 3);
    
    EXPECT_TRUE(pos1 == pos2);
    EXPECT_FALSE(pos1 == pos3);
}

TEST(PositionTest, TestAddOperator) {
    Position pos1(1, 2);
    Position pos2(1, 3);
    Position pos_result(2, 5);    

    EXPECT_EQ(pos1 + pos2, pos_result);
}

TEST(PositionTest, TestToString) {
    Position pos1(1, 2);
    std::string expectedString = "{1 , 2}";
    EXPECT_EQ(pos1.to_string(), expectedString);
}