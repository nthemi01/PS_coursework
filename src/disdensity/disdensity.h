#ifndef DISDENSITY_H
#define DISDENSITY_H
#include <string>
#include <fstream>
#include "../mapgenrator/vector_arithmetic.hpp"
#include "../mapgenrator/vector_maxmin.hpp"
#include <fstream>
#include <vector>
namespace output{
  void savefig(std::vector<std::vector<double>> density, const std::string filename, bool color_toogle);
  void savefig(std::vector<std::vector<double>> density, std::vector<std::vector<bool>> map, const std::string filename, bool color_toggle);
}
#endif
