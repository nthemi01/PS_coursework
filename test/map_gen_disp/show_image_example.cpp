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
  int window_size_x = 300, window_size_y = 200;
  int map_size_x = 60, map_size_y = 40, sample = 10;

  auto map = map_gen(map_size_x,map_size_y,1.7,sample,4);

  vector<vector<bool>> mask;

  for (auto& line : map) {
    vector<bool> maskline;
    for (auto& pixel : line) {
      maskline.push_back(pixel>0.2);
    }
    mask.push_back(maskline);
  }

  // init windows
  output::screen windows(window_size_x, window_size_y,
          "left title", "right title");
  // gen 2d map
  auto density = map_gen(map_size_x,map_size_y,1.7,sample,4);

  // just for my own test
  std::vector<std::vector<double>> half(map_size_y*sample,
            std::vector<double>(map_size_x*sample,0.5));

  for (unsigned int iter = 0; windows.notend(); ++iter) {
    // evolve and normalize
    // this can be modified to other update rules
    auto evo = (map_gen(map_size_x,map_size_y,1.0,sample,2)-half)/ 20;
    density = density + evo;
    density = (density-min2d(density))/max2d(density);

    auto img_test = output::get_img(density,mask);
    // get_img(density, map, savefig_toggle, filename) // last two are optional
    // get_img(density, savefig_toggle, filename)
    windows.assign(img_test, img_test);
    // assign()

    windows.show(iter);
  }

  return 0;
}

