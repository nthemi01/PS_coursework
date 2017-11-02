/*
 * This function is to gennerate a random map by coherent noise module.
 *
 * To directly use the 2D coherent noise map will not give a sensable map, so
 *  we use the sum of noise maps in different frequencies. The low-freq map
 *  provides the macro terrain with a large coefficient, and the high-freq map
 *  provides the micro roughness with a small coeffcient.
 * The octave controls how many components contributes to the final map, and 
 *  the highest freq is 2 to the octave-th power times of the lowest freq. With
 *  the freq's increasing, the coefficient decreases exponentially.
 *
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
