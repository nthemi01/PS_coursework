#include "gtest/gtest.h"
#include "landscape.h"
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

//Check that the map and densities are read correctly from input files
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
		 	ASSERT_DOUBLE_EQ(test_pumas[i][j],real_pumas[i][j]);
			ASSERT_DOUBLE_EQ(test_hares[i][j],real_hares[i][j]);
		}
}

//Check that the array that counts "dry" neighbors is computed correctly
TEST(landscape,neighbors)
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

//Check that hares and pumas have the correct values after 1 iterration
TEST(landscape, single_progress)
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
		 	ASSERT_DOUBLE_EQ(test_pumas[i][j],real_pumas[i][j]);
			ASSERT_DOUBLE_EQ(test_hares[i][j],real_hares[i][j]);
		}
}


//Check that hares and pumas have the correct values after 10 iterrations
TEST(landscape, 10_progress)
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

	for(int k=0;k<10;k++)
		land.progress();

	std::vector<std::vector<double> > test_hares = land.get_hares();
	std::vector<std::vector<double> > test_pumas = land.get_pumas();


	//Values on the arrays were calculated using a different method (wolfram Mathematica)
	std::vector<std::vector<double> > real_pumas {{0, 0, 0, 0, 0, 0, 0}, 
							{0, 3.36905, 4.19512, 5.3256, 5.76663,5.13713, 0},
							 {0, 3.46986, 3.98811, 4.88618, 5.12091, 4.41509,0},
							 {0, 3.06879, 3.29001, 0, 0, 3.65654, 0}, 
							{0, 2.60071, 2.78122, 0, 0, 2.5506, 0}, 
							{0, 2.03098, 2.19, 0, 0, 2.15166, 0}, 
							{0, 0, 0, 0, 0, 0, 0}}; 



       	std::vector<std::vector<double> > real_hares {{0, 0, 0, 0, 0, 0, 0},
							 {0, 25.2136, 26.0136, 26.6728, 26.5413, 24.5331, 0},
							 {0, 28.5986, 28.1866, 27.4487, 27.1147, 26.4163, 0},
							 {0, 25.805, 27.1496, 0, 0, 29.9153, 0}, 
							{0, 24.3826, 27.1328, 0,  0, 29.6774, 0}, 
							{0, 22.4783, 25.8482, 0, 0, 33.8322, 0}, 
							{0, 0, 0, 0, 0, 0, 0}}; 

	
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
			//Double numbers after 10 iterations diverge slightly between c++ code and wolfram Mathemtica,
			//so we use delta = 1e-4 tou account for that
			ASSERT_NEAR (test_pumas[i][j],real_pumas[i][j],0.0001);
			ASSERT_NEAR (test_hares[i][j],real_hares[i][j],0.0001);
		}
}




//Check that the average value of hares and pumas is correct  after 20 iterrations
TEST(landscape, averages)
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

	for(int k=0;k<20;k++)
		land.progress();

	double test_hares = land.average_hares();
	double test_pumas = land.average_pumas();

	//Values  were calculated using a different method (wolfram Mathematica)
	double real_pumas = 72.8913;
	double real_hares = 0.9653;	

			//Double numbers after 10 iterations diverge slightly between c++ code and wolfram Mathemtica,
			//so we use delta = 1e-4 tou account for that
			ASSERT_NEAR (test_pumas,real_pumas,0.0001);
			ASSERT_NEAR (test_hares,real_hares,0.0001);
}

int main(int argc,char **argv)
{
	

testing::InitGoogleTest(&argc,argv);
return RUN_ALL_TESTS();
}
