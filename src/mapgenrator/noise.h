#ifndef NOISE_H
#define NOISE_H

#include <vector>
#include <functional>
#include <algorithm>
#include <random>

namespace noise{
  double cubic_func(double x, const double param0, const double param1, const double param2, const double param3);
  std::vector<double> discrete_random_series(int size);
  std::vector<std::function<double(double)>> cubic_spline_functions(std::vector<double>& rdlist, const double step=1.0);
  std::vector<double> coherent_series(std::vector<std::function<double(double)>> splines_function, int samples=20, const double step=1.0);
  std::vector<double> coherent_series(int size, int samples=20);
  std::vector<std::vector<double>> coherent_map(int size1, int size2, int sample1=20, int sample2=20);
};

#endif
