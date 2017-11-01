#include "gtest/gtest.h"
#include "../include/landscape.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream


TEST(landscape, initial_densities)
{
	const std::string kMapPath = "test_map1.dat";
	const std::string kHaresPath = "test_hares1.dat";
	const std::string kPumasPath = "test_pumas1.dat";
	Params pars;
	pars.r = 0.8;
	pars.a = 0.04;
	pars.b = 0.02;
	pars.m = 0.06;
	pars.k = 0.2;
	pars.l = 0.2;
	pars.dt = 0.4;
	landscape land(pars,kMapPath,kPumasPath,kHaresPath);

	std::vector<std::vector<double> > test_hares = land.get_hares();
	std::vector<std::vector<double> > test_pumas = land.get_pumas();
	
	std::vector<std::vector<double> > real_pumas {{0,0,0,0,0,0,0},
					   {0,2,3,4,5,4,0},
                                           {0,1,2,3,3,1,0}, 
					   {0,3,2,0,0,3,0},
					   {0,2,2,0,0,1,0},
					   {0,1,1,0,0,1,0},	
					   {0,0,0,0,0,0,0}};

	std::vector<std::vector<double> > real_hares {{0,0,0,0,0,0,0},
					   {0,1,2,3,4,2,0},
                                           {0,4,3,2,3,1,0}, 
					   {0,1,2,0,0,4,0},
					   {0,2,3,0,0,1,0},
					   {0,1,2,0,0,3,0},	
					   {0,0,0,0,0,0,0}};

	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
		 	ASSERT_DOUBLE_EQ(real_pumas[i][j],test_pumas[i][j]);
			ASSERT_DOUBLE_EQ(real_hares[i][j],test_hares[i][j]);
		}
}


TEST(landscape, progress)
{
	const std::string kMapPath = "test_map1.dat";
	const std::string kHaresPath = "test_hares1.dat";
	const std::string kPumasPath = "test_pumas1.dat";
	Params pars;
	pars.r = 0.8;
	pars.a = 0.04;
	pars.b = 0.02;
	pars.m = 0.06;
	pars.k = 0.2;
	pars.l = 0.2;
	pars.dt = 0.4;
	landscape land(pars,kMapPath,kPumasPath,kHaresPath);

	land.progress();
	std::vector<std::vector<double> > test_hares = land.get_hares();
	std::vector<std::vector<double> > test_pumas = land.get_pumas();

	std::vector<std::vector<double> > real_pumas {{0,0,0,0,0,0,0},
					   {0,2,3,4,5,4,0},
                                           {0,1,2,3,3,1,0}, 
					   {0,3,2,0,0,3,0},
					   {0,2,2,0,0,1,0},
					   {0,1,1,0,0,1,0},	
					   {0,0,0,0,0,0,0}};

	std::vector<std::vector<double> > real_hares {{0,0,0,0,0,0,0},
					   {0,1,2,3,4,2,0},
                                           {0,4,3,2,3,1,0}, 
					   {0,1,2,0,0,4,0},
					   {0,2,3,0,0,1,0},
					   {0,1,2,0,0,3,0},	
					   {0,0,0,0,0,0,0}};
	//land.printhares();
	
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
		 	ASSERT_DOUBLE_EQ(real_pumas[i][j],test_pumas[i][j]);
			ASSERT_DOUBLE_EQ(real_hares[i][j],test_hares[i][j]);
		}
}


int main(int argc,char **argv)
{
	

testing::InitGoogleTest(&argc,argv);
return RUN_ALL_TESTS();
}
