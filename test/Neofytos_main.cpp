#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include "../include/landscape.h"
#include <fstream>
#include <vector>

int main()
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
	land.printhares();
	land.progress();
	land.printhares();
}


