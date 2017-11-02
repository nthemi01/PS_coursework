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
  const unsigned int xx = 60, yy = 40, samples = 10;
  auto map = map_gen(xx,yy,1.7,samples,4);
  auto density = map_gen(xx,yy,1.7,samples,4);
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
  fout << xx << ' ' << yy << '\n' << mask;
  fout << std::flush;
  fout.close();

  return 0;
}

