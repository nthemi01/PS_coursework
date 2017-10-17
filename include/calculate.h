#include <iostream>
#include <math.h>
#include <vector>

#ifndef CALCULATE_H
#define CALCULATE_H

class calculate {
private:

	double r, a, b, m, k, l ,dt, T; // where ... 
	std::vector<std::vector<double> > pumas; //the density matrix of pumas
	std::vector<std::vector<double> > hares; // the density matrix of hares
				//also maybe something about the squares filled with water
public:

	calculate();
	void progress();
	double average_hares();
	double average_pumas();
	void printPPM();

void printx();//just a temporary test function
};

#endif
