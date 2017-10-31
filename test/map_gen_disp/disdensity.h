#ifndef DISDENSITY_H
#define DISDENSITY_H
#include <string>
#include <fstream>
namespace output{
  void savefig(std::vector<std::vector<double>> map, const std::string filename, bool color);
}
#endif
