#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <valarray>
#include <fstream> //for reading in files
#include <ctime> //for seeding random number generator
#include <string.h>


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
	double r, a, b, m, k, l ,dt; // where ... 
	std::vector<std::vector<double> > pumas; //the density matrix of pumas
	std::vector<std::vector<double> > hares; // the density matrix of hares
	std::vector<std::vector<double> > map; // map matrix


	std::vector<std::vector<bool> > grid; // 1 represents land, 0 represents water 
	std::vector<std::vector<int> > N; // the number of "dry" neighboring squares

	std::vector<std::vector<double> > pumas_old; //temporary storing the  density matrix of pumas for use from the progress function
	std::vector<std::vector<double> > hares_old;
	
	std::string pumaDpath; // path of density & map files
	std::string hareDpath;
	std::string mapPath;
	

public:

	landscape(const struct Params &, const std::string , const std::string, const std::string); //constractor set the right grid size, initiates densities, calculates number of neighbors
	void progress(); // calculate the density values of hares and pumas for the next time step
	double average_hares(); //return the average value of hares along the "dry" squares
	double average_pumas();

	void printhares(); //prints to the screen the density matrix of hares
	void printpumas();
	void printPPM();

	//A neat way to resize vectors of vectors. As soon as I figure out how, I will use prototype to reduce these three to one function.
	//void resizeVec( std::vector<std::vector<bool> > &vec , const unsigned short ROWS , const unsigned short COLUMNS );
	//void resizeVec( std::vector<std::vector<int> > &vec , const unsigned short ROWS , const unsigned short COLUMNS );
	//void resizeVec( std::vector<std::vector<double> > &vec , const unsigned short ROWS , const unsigned short COLUMNS );

	std::vector<std::vector<double> > get_hares();//returns a vector of vectors with size grid_size_x * grid_size_y with the density of hares
	std::vector<std::vector<double> > get_pumas();

	//helper functions for constructor
	int readinfile(const std::string, std::vector<std::vector<double> >&);
	void generateRandomDensity(std::vector<std::vector<double> > &, std::vector<std::vector<double> > const &);


};

struct Params{double r,a,b,m,k,l,dt;};


#endif
