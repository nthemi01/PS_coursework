#ifndef NOISE_H
#define NOISE_H

#include <vector>
#include <functional>
#include <algorithm>
#include <random>

namespace noise{
  double cubic_func(double x, const double param0, const double param1, const double param2, const double param3);
  // input:
  //   x: independent varibale
  //   param0 - param3: coefficients associated with x to the i th
  // return the value of the cubic polynomial function
  
  std::vector<double> discrete_random_series(int size);
  // input:
  //   size: the number of regions for following interpolation
  //   
  // return a series of random numbers in length of size+1

  std::vector<std::function<double(double)>> cubic_spline_functions(std::vector<double>& rdlist, const double step=1.0);
  // input:
  //   rdlist: random number series
  //   step: defined interval between two numbers in the random number series
  // return a vector of function object generated by spline interpolation algorithm
  
  std::vector<double> coherent_series(std::vector<std::function<double(double)>> splines_function, int samples=20, const double step=1.0);
  // input:
  //   splines_function: a vector of spline function object
  //   samples: number of points between two fixed random numbers
  //   step: defined interval between two numbers in the random number series
  // return a coherent noise series in length of size*samples+1

  std::vector<double> coherent_series(int size, int samples=20);
  // combine the steps above
  // return a coherent noise series in length of size*samples+1
  
  std::vector<std::vector<double>> coherent_map(int size1, int size2, int sample1=20, int sample2=20);
  // return a 2D transposed coherent noise map in size of (size2*samples2+1,size1*samples1+1)
};

#endif
