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
  // Inputs:
  //   density: density data
  //   savefig: toggle to control save image or not
  //   filename: file name of ppm file
  //  return a CImg object for display
  cimg_library::CImg<unsigned int> get_img(std::vector<std::vector<double>> density, std::vector<std::vector<bool>> map, bool savefig = false, const std::string filename = "tmp.ppm");
  // Inputs:
  //   density: density data
  //   map: map data
  //   savefig: toggle to control save image or not
  //   filename: file name of ppm file
  //  return a CImg object for display


  class screen {
    private:
      std::vector<std::vector<bool>> map;
      // map data
      unsigned int window_size_x, window_size_y;
      // size of window to display densities
      cimg_library::CImgDisplay disp_left, disp_right;
      // two windows for display
      cimg_library::CImg<unsigned int> img_left, img_right;
      // images for two windows

    public:
      screen(unsigned int window_size_x, unsigned int window_size_y, const char* title_left = 0, const char* title_right = 0);
      // construct two windows for display
      // inputs:
      //   window_size_x, window_size_y: the sizes of windows
      //   title_left, title_right: titles of windows
      void assign(cimg_library::CImg<unsigned int> img_left, cimg_library::CImg<unsigned int> img_right);
      // assign images to two windows
      // inputs:
      //   img_left, img_right: images passed to windows
      void show(unsigned int iter);
      // update the windows
      // input:
      //   iteration number for showing on the image
      bool notend();
      // check the window is closed
      // return true if the window is not closed
  };
}
#endif
