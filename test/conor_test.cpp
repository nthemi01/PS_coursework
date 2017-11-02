#include "gtest/gtest.h"
#include "../include/landscape.h"

// Test: If the same file read into pumas and hares is read in corretly and the two densities are the same.
TEST(ConstructorTestSuite, ReadInFileTest1)
{
    const std::string kMapPath = "small.dat"; //50 by 50
    const std::string kInitialDensityPath = "smallDensity.dat"; //50 by 50 

    const int kMapSize = 50;
    Params pars; pars.r = 0.8; pars.a = 0.04; pars.b = 0.02; pars.m = 0.06; pars.k = 0.2;
    pars.l = 0.2; pars.dt = 0.4;

    landscape land(pars,kMapPath,kInitialDensityPath,kInitialDensityPath);

    std::vector<std::vector<double> > pumas = land.get_pumas();
    std::vector<std::vector<double> > hares = land.get_hares();


    for(int x=0; x<kMapSize; x++)
        for(int y=0; y<kMapSize; y++)
            ASSERT_EQ(pumas[x][y],hares[x][y]);

}

// Test: If two different file sizes are provided the constructor throws an exception
TEST(ConstructorTestSuite, ReadInFileTest2)
{
    const std::string kMapPath = "islands.dat"; //1000 by 800
    const std::string kInitialDensityPath = "smallDensity.dat"; //50 by 50 

    Params pars; pars.r = 0.8; pars.a = 0.04; pars.b = 0.02; pars.m = 0.06; pars.k = 0.2;
    pars.l = 0.2; pars.dt = 0.4;

    try {
            landscape land(pars,kMapPath,kInitialDensityPath,kInitialDensityPath);
            FAIL() << "Expected std::invalid_argument";
        }
    catch(std::invalid_argument const & err) {
            EXPECT_EQ(err.what(),std::string("ReadInFile failed because the file was not the same size as the Map file"));
        }
    catch(...) {
            FAIL() << "std::invalid_argument";
        }
}

// Test that a density path is not required
TEST(ConstructorTestSuite, ReadInFileTest3)
{
    const std::string kMapPath = "small.dat"; //50 by 50
    const std::string kInitialDensityPath = "smallDensity.dat"; //50 by 50 

    Params pars; pars.r = 0.8; pars.a = 0.04; pars.b = 0.02; pars.m = 0.06; pars.k = 0.2;
    pars.l = 0.2; pars.dt = 0.4;
    
    try{
        landscape land(pars,kMapPath);
    }
    catch(...)
    {
        FAIL() << "Constructor failed to handle optional argument for initial density path";
    }   
}

// Test: wrong parameters are handled
TEST(ConstructorTestSuite, WrongParamsTest1)
{
    const std::string kMapPath = "small.dat"; //50 by 50

    Params pars; pars.r = -1; pars.a = 0.04; pars.b = -0.2; pars.m = 0.06; pars.k = 0.2;
    pars.l = 0.2; pars.dt = 0.0;
    
    landscape land(pars,kMapPath);
    
}

TEST(ConstructorTestSuite, WrongDensitiesTest1)
{
    const std::string kMapPath = "small.dat"; //50 by 50

    Params pars; pars.r = 0.8; pars.a = 0.04; pars.b = 0.02; pars.m = 0.06; pars.k = 0.2;
    pars.l = 0.2; pars.dt = 0.4;
    
    landscape land(pars,kMapPath);
}



int main(int argc,char **argv)
{
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
