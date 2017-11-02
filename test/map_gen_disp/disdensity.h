#ifndef DISDENSITY_H
#define DISDENSITY_H
#include <string>
#include <fstream>
#include <vector>
#include "CImg.h"
#include "vector_arithmetic.hpp"
#include "vector_maxmin.hpp"

namespace output{
  cimg_library::CImg<unsigned int> display(std::vector<std::vector<double>> density, bool savefig = false, const std::string filename = "tmp.ppm");
  cimg_library::CImg<unsigned int> display(std::vector<std::vector<double>> density, std::vector<std::vector<bool>> map, bool savefig = false, const std::string filename = "tmp.ppm");
}
#endif
