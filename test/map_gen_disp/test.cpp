#include "noise.h"
#include "randommap.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "disdensity.h"

using std::vector;

int main(){
  auto map = setmap(40,40,1.7,10,4);
  vector<vector<bool>> mask;

  for (auto& line : map) {
    vector<bool> maskline;
    for (auto& pixel : line) {
      maskline.push_back(pixel>0.2);
    }
    mask.push_back(maskline);
  }

  auto density = setmap(40,40,1.7,10,4);

  output::savefig(density, mask, "test.ppm", true);
  return 0;
}

