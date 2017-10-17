#ifndef RANDOMMAP_H
#define RANDOMMAP_H

#include <vector>
#include "vector_arithmetic.hpp"
#include "vector_maxmin.hpp"
#include "noise.h"

std::vector<std::vector<double>> setmap(int x, int y, double index = 1.7, const int samples = 10, const int octave = 4);

#endif
