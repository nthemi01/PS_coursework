#ifndef RANDOMMAP_H
#define RANDOMMAP_H

#include <vector>
#include "include/vector_arithmetic.hpp"
#include "include/vector_maxmin.hpp"
#include "include/noise.h"

std::vector<std::vector<double>> map_gen(int x, int y, double index = 1.7, const int samples = 10, const int octave = 4);

// input:
//   x,y : the size of output map
//   index : the index of the power function applied on values of the map to make the terrain steeper (index>1) or smoother (index<1)
//   samples : number of points between two neighbor random points
//   octave : order of the highest frequency noise
// return a 2d random map (values from 0 to 1) in size of (x,y)

#endif
