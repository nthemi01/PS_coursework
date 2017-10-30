#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include "../include/landscape.h"
#include <fstream>
#include <vector>

int main()
{
const std::string kMapPath = "../lib/small.dat";
const std::string kInitialDensityPath = "../lib/smallDensity.dat";


Params pars;
pars.r = 0.8;
pars.a = 0.04;
pars.b = 0.02;
pars.m = 0.06;
pars.k = 0.2;
pars.l = 0.2;
pars.dt = 0.4;



landscape land(pars,kMapPath);

land.printhares();
land.printpumas();

}




