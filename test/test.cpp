#include "gtest/gtest.h"
#include "landscape.h"

TEST(LandTestSuit1, TestCase1)
{
    EXPECT_EQ(-1,-1);
}

TEST(LandTestSuit2, TestCase2)
{
    ASSERT_EQ(8,8);
}

int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
