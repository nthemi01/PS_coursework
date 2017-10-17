#include <iostream>
#include "calculate.h"


calculate::calculate()
{
	// constractor will set the size of pumas & hares
	// fill them (if this will be a seperate class)
}

void calculate::progress()
{
	// progress function will be the one doing the actual computation for both Pumas and Hares
	// and calculating the densities for for the next time step.
}

double calculate::average_hares()
{
	// when average function is called it will return the average value of Hares at that time.
}


double calculate::average_pumas()
{
	// when average function is called it will return the average value of Pumas at that time.
}

void calculate::printPPM()
{
	//export a PPM file when called
}

void calculate::printx()
{
	int x=5;	
	std::cout<<x<<std::endl;
}


