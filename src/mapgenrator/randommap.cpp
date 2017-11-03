// Copyright [2017] <Mengxuan Zhu>

#include "../../include/randommap.h"
#include "../../include/noise.h"

std::vector<std::vector<double>> map_gen(unsigned int x, unsigned int y,
        double index, const unsigned int samples, const unsigned int octave) {
  if (samples == 0)
    throw "samples must be greater than 0\n";
  if (octave == 0)
    throw "octave must be greater than 0\n";
  int modfactor = 1 << octave;

  // generate a map of size (xmod, ymod)
  // they are smallest multiples of 2^octave, greater than x,y
  int xmod = (static_cast<int>(x/modfactor)+2)*modfactor;
  int ymod = (static_cast<int>(y/modfactor)+2)*modfactor;

  auto map = std::vector<std::vector<double>>(ymod*samples+1,
          std::vector<double>(xmod*samples+1, 0));
  for (unsigned int i = octave; i > 0; --i) {
    unsigned int tmp_factor = 1 << (i-1);
    map = map + noise::coherent_map(
            ymod/tmp_factor,
            xmod/tmp_factor,
            samples*tmp_factor,
            samples*tmp_factor)
        /(modfactor >> i);
  }

  // reshape the map to the size (x,y)
  unsigned int xres = (xmod - x)*samples;
  unsigned int yres = (ymod - y)*samples;
  for (unsigned int i = 0; i <= yres; ++i)
    map.pop_back();
  for (auto& yelem : map)
    for (unsigned int i = 0; i <= xres; ++i)
      yelem.pop_back();

  map = (map-min2d(map))/max2d(map);
  map = pow(map, index);

  return map;
}

std::vector<std::vector<double>> steepen(
        std::vector<std::vector<double>> map, double index) {
  map = (map-min2d(map))/max2d(map);
  map = pow(map, index);
  return map;
}
