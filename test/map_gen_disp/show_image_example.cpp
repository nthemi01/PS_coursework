#include "noise.h"
#include "randommap.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "disdensity.h"
#include "CImg.h"

using std::vector;
using namespace cimg_library;

int main(){

/*
 * test saving a masked map
  auto map = map_gen(40,40,1.7,10,4);
  vector<vector<bool>> mask;

  for (auto& line : map) {
    vector<bool> maskline;
    for (auto& pixel : line) {
      maskline.push_back(pixel>0.2);
    }
    mask.push_back(maskline);
  }

  auto density = setmap(40,40,1.7,10,4);
  auto dump = output::display(density, true, "test1.ppm");
  dump = output::display(density, mask, true, "test2.ppm");
*/


  // set parameters
  int window_size_x = 300, window_size_y = 400;
  int map_size_x = 60, map_size_y = 80, sample = 10;
  int img_size_x = map_size_x*sample, img_size_y = map_size_y*sample;

  // init windows
  CImgDisplay disp_left(window_size_x,window_size_y,
          "colorscale map",0,false,true);
  CImgDisplay disp_right(window_size_x,window_size_y,
          "grayscale map",0,false,true);
  disp_left.move(
          (CImgDisplay::screen_width() - disp_right.width() - disp_left.width())/2,
          (CImgDisplay::screen_height() - disp_right.height())/2);
  disp_right.move(
          disp_left.window_x() + 8 + disp_left.window_width(),
          disp_left.window_y());


  // generate a map for test
  auto density = map_gen(map_size_x,map_size_y,1.7,sample,4);
  for (int iter = 0 ;
          !disp_right.is_closed() && !disp_left.is_closed() &&
          !disp_right.is_keyQ() && !disp_right.is_keyESC() &&
          !disp_left.is_keyQ() && !disp_left.is_keyESC(); ++iter) {
    // set evolution varible
    std::vector<std::vector<double>> half(map_size_y*sample,
            std::vector<double>(map_size_x*sample,0.5));
    auto evo = (map_gen(map_size_x,map_size_y,1.0,sample,1)-half)/ 5;
    if (iter%20==0)
      // display density on disp_left
      // refresh rate: per 20 iters
      output::display(density).display(disp_left);
    // evolve and normalize
    density = density + evo;
    density = (density-min2d(density))/max2d(density);
    // display density on disp_right
    // refresh rate: per iter
    output::display(density).display(disp_right);
  }

  return 0;
}

