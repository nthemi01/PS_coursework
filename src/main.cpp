#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include "../include/landscape.h"
#include <fstream>
#include <vector>

int main()
{
std::string mapPath = "../lib/small.dat";
std::string animalPath = "../lib/smallDensity.dat";


Params pars;
pars.r = 0.8;
pars.a = 0.04;
pars.b = 0.02;
pars.m = 0.06;
pars.k = 0.2;
pars.l = 0.2;
pars.dt = 0.4;

//landscape* lscap = new landscape(pars, mapPath,animalPath, animalPath);
//lscap->printhares();



landscape lscap(pars,mapPath,animalPath,animalPath);

std::vector<std::vector<double> > animal;
int grid_size_x=52, grid_size_y=52;

std::stringstream index;


lscap.progress();

//lscap.printhares();
                                                        
}



