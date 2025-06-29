#include "gtest/gtest.h"
#include "max.h"
TEST(Max, MaxOf3and5){
    EXPECT_EQ(5,max(3,5));
}