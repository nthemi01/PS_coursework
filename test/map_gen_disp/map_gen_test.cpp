#include "../../include/randommap.h"
#include "gtest/gtest.h"
#include <vector>

using std::vector;

TEST(mapgenTestSuite, NormalSizeCheck){
    vector<vector<double>> map = map_gen(30,20,1.0,10,4);
    EXPECT_EQ(map.size(), 200);
    EXPECT_EQ(map[0].size(), 300);
}

TEST(mapgenTestSuite, NarrowSizeCheck1){
    vector<vector<double>> map = map_gen(1,10,1.0,10,4);
    EXPECT_EQ(map.size(), 100);
    EXPECT_EQ(map[0].size(), 10);
}

TEST(mapgenTestSuite, NarrowSizeCheck2){
    vector<vector<double>> map = map_gen(10,1,1.0,10,4);
    EXPECT_EQ(map.size(), 10);
    EXPECT_EQ(map[0].size(), 100);
}

TEST(mapgenTestSuite, WhiteNoiseSizeCheck){
    vector<vector<double>> map = map_gen(30,20,1.0,1,4);
    EXPECT_EQ(map.size(), 20);
    EXPECT_EQ(map[0].size(), 30);
}

TEST(mapgenTestSuite, ZeroSampleSizeCheck){
    vector<vector<double>> map = map_gen(30,20,1.0,0,4);
    FAIL();
}

TEST(mapgenTestSuite, ZeroOctaveSizeCheck){
    vector<vector<double>> map = map_gen(30,20,1.0,1,0);
    FAIL();
}



int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
