/*
 * This module is to generate coherent noise 1D series or 2D map.
 * Here are brief introduction to the algorithm:
 *   1D series:
 *     1. Generate 1D array filled by random numbers;
 *     2. Apply cubic spline interpolation algorithm on the random series, 
 *         and get the parameters of cubic functions
 *     3. Use the spline functions to fill the gap between random numbers.
 *
 *   2D map:
 *     1. Generate a series of 1D cohenrent noise series along x-axis, 
 *         then along y-axis, there are discrete random series;
 *     2. Apply interpolation algorithm on the series along y-axis;
 *     3. Fill the empty band between coherent noise series along x-axis 
 *         by cubic spline funcitons.
*/

#ifndef RANDOMMAP_H
#define RANDOMMAP_H

#include <vector>
#include "vector_arithmetic.hpp"
#include "vector_maxmin.hpp"
#include "noise.h"

std::vector<std::vector<double>> map_gen(unsigned int x, unsigned int y, double index = 1.7, const unsigned int samples = 10, const unsigned int octave = 4);

// input:
//   x,y : the size of output map
//   index : the index of the power function applied on values of the map to make the terrain steeper (index>1) or smoother (index<1)
//   samples : number of points between two neighbor random points
//   octave : order of the highest frequency noise
// return a 2d random map (values from 0 to 1) in size of (x,y)

#endif
