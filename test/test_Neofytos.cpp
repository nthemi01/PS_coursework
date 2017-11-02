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


	//Values on the two arrays are the same as the input file	
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


	//Values on the arrays were calculated using a different method (wolfram Mathematica)
	std::vector<std::vector<double> > real_pumas  {{0, 0, 0, 0, 0, 0, 0}, 
							{0, 1.968, 2.896, 3.92, 4.72, 3.808, 0}, 
							{0, 1.328, 2.08, 2.976, 3., 1.544, 0}, 
							{0, 2.632, 2.064, 0, 0, 2.704, 0},
							{0, 1.984, 1.92, 0, 0, 1.144, 0}, 
							{0, 1.064, 1.072, 0, 0, 1., 0}, 
							{0, 0,     0,     0, 0, 0, 0}};





       	std::vector<std::vector<double> > real_hares   {{0, 0, 0, 0, 0, 0, 0}, 
							{0, 1.608, 2.624, 3.688, 4.64, 2.592, 0},
							{0,4.656, 3.704, 2.784, 3.656, 1.784, 0}, 
							{0, 1.672, 2.656, 0, 0, 4.608, 0}, 
							{0, 2.496, 3.624, 0, 0, 1.704, 0}, 
							{0, 1.464, 2.608, 0,0, 3.752, 0}, 
							{0, 0, 0, 0, 0, 0, 0}};




	
	                 for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
		 	//ASSERT_DOUBLE_EQ(real_pumas[i][j],test_pumas[i][j]);
			ASSERT_DOUBLE_EQ(real_hares[i][j],test_hares[i][j]);
		}
}



TEST(landscape, neighbors)
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

	std::vector<std::vector<int> > test_neighbors = land.get_neighbors();


	//Values on the array were evaluated by hand
	std::vector<std::vector<int> > real_neighbors    {{0, 0, 0, 0, 0, 0, 0}, 
							{0, 2, 3, 3, 3, 2, 0}, 
							{0, 3, 4, 3, 3, 3, 0}, 
							{0, 3, 3, 0, 0, 2, 0}, 
							{0, 3, 3, 0, 0, 2, 0}, 
							{0, 2, 2, 0, 0, 1, 0}, 
							{0, 0, 0, 0, 0, 0, 0}}; 

	
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
			ASSERT_EQ(real_neighbors[i][j],test_neighbors[i][j]);
		}
}




int main(int argc,char **argv)
{
	

testing::InitGoogleTest(&argc,argv);
return RUN_ALL_TESTS();
}
