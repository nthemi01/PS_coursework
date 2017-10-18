#include <iostream>
#include <math.h>
#include <vector>
#include <valarray>

#ifndef LANDSCAPE_H
#define LANDSCAPE_H


class landscape {
private:
	int grid_size_x, grid_size_y;
	double r, a, b, m, k, l ,dt; // where ... 
	std::vector<std::vector<double> > pumas; //the density matrix of pumas
	std::vector<std::vector<double> > hares; // the density matrix of hares


	std::vector<std::vector<bool> > grid; // 1 represents land, 0 represents water 
	std::vector<std::vector<int> > N; // the number of "dry" neighboring squares

	std::vector<std::vector<double> > pumas_old; //the density matrix of pumas
	std::vector<std::vector<double> > hares_old; // the density matrix of hares
				//also maybe something about the squares filled with water
public:

	landscape();
	void progress();
	double average_hares();
	double average_pumas();
	void printPPM();

	void printhares();
	void printpumas();

	void printx();//just a temporary test function

	
	void resizeVec( std::vector<std::vector<bool> > &vec , const unsigned short ROWS , const unsigned short COLUMNS );
	void resizeVec( std::vector<std::vector<int> > &vec , const unsigned short ROWS , const unsigned short COLUMNS );
	void resizeVec( std::vector<std::vector<double> > &vec , const unsigned short ROWS , const unsigned short COLUMNS );
};

#endif
