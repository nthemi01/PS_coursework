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

int main(){

  // test saving a masked map
  auto map = map_gen(40,40,1.7,10,4);
  auto density = map_gen(40,40,1.7,10,4);
  vector<vector<bool>> mask;

  for (auto& line : map) {
    vector<bool> maskline;
    for (auto& pixel : line) {
      maskline.push_back(pixel>0.2);
    }
    mask.push_back(maskline);
  }

  auto dump = output::get_img(density, true, "test1.ppm");
  dump = output::get_img(density, mask, true, "test2.ppm");

  std::ofstream fout("test.dat");
  fout << "400 400 " << mask;
  fout << std::flush;
  fout.close();

  return 0;
}

