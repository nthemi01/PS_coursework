#ifndef DISDENSITY_H
#define DISDENSITY_H
#include <string>
#include <fstream>
#include <vector>
#include "CImg.h"
#include "vector_arithmetic.hpp"
#include "vector_maxmin.hpp"

namespace output{
  cimg_library::CImg<unsigned int> get_img(std::vector<std::vector<double>> density, bool savefig = false, const std::string filename = "tmp.ppm");
  cimg_library::CImg<unsigned int> get_img(std::vector<std::vector<double>> density, std::vector<std::vector<bool>> map, bool savefig = false, const std::string filename = "tmp.ppm");

  class screen {
    private:
      std::vector<std::vector<bool>> map;
      unsigned int window_size_x, window_size_y;
      cimg_library::CImgDisplay disp_left, disp_right;
      cimg_library::CImg<unsigned int> img_left, img_right;

    public:
      screen(unsigned int window_size_x, unsigned int window_size_y, const char* title_left = 0, const char* title_right = 0);
      void assign(cimg_library::CImg<unsigned int> img_left, cimg_library::CImg<unsigned int> img_right);
      void show(unsigned int iter);
      bool notend();
  };
}
#endif
