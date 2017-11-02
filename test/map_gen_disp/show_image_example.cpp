#include "noise.h"
#include "randommap.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "disdensity.h"
#include "CImg.h"

#ifdef GTEST
#include "gtest/gtest.h"
#endif

using std::vector;
using cimg_library::CImg;

int main(){

  // set parameters
  int window_size_x = 400, window_size_y = 400;
  int map_size_x = 40, map_size_y = 40, sample = 10;
  int img_size_x = map_size_x*sample, img_size_y = map_size_y*sample;


  // init windows
  output::screen windows(window_size_x, window_size_y, "left", "right");
  auto density = map_gen(map_size_x,map_size_y,1.7,sample,4);

  std::vector<std::vector<double>> half(map_size_y*sample,
            std::vector<double>(map_size_x*sample,0.5));

  for (unsigned int iter = 0; windows.notend(); ++iter) {
    // evolve and normalize
    // this can be modified to other update rules
    auto evo = (map_gen(map_size_x,map_size_y,1.0,sample,2)-half)/ 20;
    density = density + evo;
    density = (density-min2d(density))/max2d(density);
    auto img_test = output::get_img(density);

    windows.assign(img_test, img_test);
    windows.show(iter);
  }

  return 0;
}

