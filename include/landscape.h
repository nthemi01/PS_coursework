#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <valarray>
#include <fstream> //for reading in files
#include <ctime> //for seeding random number generator
#include <string.h>
#include <stdexcept> //for throw std::invalid_argument

#ifndef LANDSCAPE_H
#define LANDSCAPE_H

//Info for the rest of the programmers:
//	Fow now the constructor doesn't accept arguments
//	To go to the next time step use: progress()
//	To get the values of hares and pumas use:
//		get_hares();
//		get_pumas();


class landscape {
private:
	int grid_size_x, grid_size_y;  //spacial dimensions of the grid
	double r, a, b, m, k, l ,dt;  
	std::vector<std::vector<double> > pumas; //the density matrix of pumas
	std::vector<std::vector<double> > hares; // the density matrix of hares
	std::vector<std::vector<bool> > map; // map matrix


	//std::vector<std::vector<bool> > grid; // 1 represents land, 0 represents water 
	std::vector<std::vector<int> > N; // the number of "dry" neighboring squares

	std::vector<std::vector<double> > pumas_old; //temporary storing the  density matrix of pumas for use from the progress function
	std::vector<std::vector<double> > hares_old;
	
	std::string pumaDpath; // path of density & map files
	std::string hareDpath;
	std::string mapPath;


	std::vector< std::vector<double> >::iterator row; //2d vector iterators used by the average_hares and average_pumas functions
	std::vector<double>::iterator col;

	
public:

	landscape(const struct Params &, const std::string , const std::string, const std::string); 
	landscape(const Params &, const std::string);
	//constractor set the right grid size, initiates densities, calculates number of neighbors
	
	void progress(); // calculate the density values of hares and pumas for the next time step
	double average_hares(); //return the average value of hares along the "dry" squares
	double average_pumas();

	void printhares(); //prints to the screen the density matrix of hares
	void printpumas();
	void printPPM();

	std::vector<std::vector<double> > get_hares();//returns a vector of vectors with size grid_size_x * grid_size_y with the density of hares
	std::vector<std::vector<double> > get_pumas();
	std::vector<std::vector<bool> > get_map();
	
	//helper functions for constructor
	int readinfile(const std::string, std::vector<std::vector<double> >&);
	int readinfile(const std::string, std::vector<std::vector<bool> >&);
	//void generateRandomDensity(std::vector<std::vector<double> > &, std::vector<std::vector<double> > const &);
	void generateRandomDensity(std::vector<std::vector<double> > &, std::vector<std::vector<bool> > const &);

	operator bool() {return false;};
};

struct Params{double r,a,b,m,k,l,dt;};


#endif
