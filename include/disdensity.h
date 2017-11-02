#ifndef DISDENSITY_H
#define DISDENSITY_H

#include <string>
#include <fstream>
#include <vector>
#include "../include/CImg.h"
#include "../include/vector_arithmetic.hpp"
#include "../include/vector_maxmin.hpp"
namespace output{
  cimg_library::CImg<unsigned int> display(std::vector<std::vector<double>> density, bool savefig = false, const std::string filename = "tmp.ppm");
  // input:
  //   density: density map of either hares or pumas
  //   savefig: toggle to save density to a ppm file
  //   filename: filename of the ppm file
  // return a cimg_library::CImg<unsigned> object for showing on screen
  cimg_library::CImg<unsigned int> display(std::vector<std::vector<double>> density, std::vector<std::vector<bool>> map, bool savefig = false, const std::string filename = "tmp.ppm");
  // input:
  //   density: density map of either hares or pumas
  //   map: terrain map
  //   savefig: toggle to save density to a ppm file
  //   filename: filename of the ppm file
  // return a cimg_library::CImg<> object for showing on screen

}
#endif
