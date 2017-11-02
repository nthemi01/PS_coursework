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
using namespace cimg_library;

int main(){

  // set parameters
  int window_size_x = 550, window_size_y = 450;
  int map_size_x = 60, map_size_y = 80, sample = 5;
  int img_size_x = map_size_x*sample, img_size_y = map_size_y*sample;

  // init windows
  CImgDisplay disp_left(window_size_x,window_size_y,
          "left map",0,false,true);
  CImgDisplay disp_right(window_size_x,window_size_y,
          "right map",0,false,true);
  disp_left.move(
          (CImgDisplay::screen_width() - disp_right.width() - disp_left.width())/2,
          (CImgDisplay::screen_height() - disp_right.height())/2);
  disp_right.move(
          disp_left.window_x() + 8 + disp_left.window_width(),
          disp_left.window_y());


  const unsigned int black[] = { 0,0,0 };
  // generate a map for test
  auto density = map_gen(map_size_x,map_size_y,1.7,sample,4);
  for (int iter = 0 ;
          !disp_right.is_closed() && !disp_left.is_closed() &&
          !disp_right.is_keyQ() && !disp_right.is_keyESC() &&
          !disp_left.is_keyQ() && !disp_left.is_keyESC(); ++iter) {

    std::vector<std::vector<double>> half(map_size_y*sample,
            std::vector<double>(map_size_x*sample,0.5));

    if (iter%20==0)

      // display density on disp_left
      // refresh rate: per 20 iters
      output::display(density).display(disp_left);

    // evolve and normalize
    // this can be modified to other update rules
    auto evo = (map_gen(map_size_x,map_size_y,1.0,sample,2)-half)/ 20;
    density = density + evo;
    density = (density-min2d(density))/max2d(density);

    // display density on disp_right per iter
    // display the iter num at upleft corner
    output::display(density).
        draw_text(2, 2, "iter = %d", black, 0, 1,
                disp_right.width()/20, iter).
        display(disp_right);
  }

  return 0;
}

