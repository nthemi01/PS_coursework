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

  vector<vector<double>> colormap;

  for (int i = 0; i < 50; ++i) {
    vector<double> colorline;
    for (double j = 0; j < 400; j += 1) {
      colorline.push_back(j/400);
    }
    colormap.push_back(colorline);
  }

  output::savefig(colormap, "colorbar.ppm", true);

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
/*
  CImg<unsigned char> img(800,640,1,3); // 640x800 image, 8bit color
  img.fill(0); // fill image with black (0)
  const unsigned char purple[] = {255, 0, 255}; // define purple
  img.draw_text(100,100,"hello world",purple);
  img.display("Hello World display");
*/

  return 0;
}

