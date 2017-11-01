// Copyright [2017] <Mengxuan Zhu>

#include "../../include/disdensity.h"

cimg_library::CImg<unsigned int>  output::display(
        std::vector<std::vector<double>> density,
        bool savefig, const std::string filename) {
  std::ofstream fout(filename);
  auto norm_density = (density-min2d(density))/max2d(density);
  int size_x = norm_density[0].size();
  int size_y = norm_density.size();

  if (savefig) {
     fout << "P3\n";
     fout << norm_density[0].size() << ' ' << norm_density.size() << '\n';
     fout << "255\n";
  }

  int x_coord = 0, y_coord = 0;
  cimg_library::CImg<unsigned int> res(size_x, size_y, 1, 3);
  res.fill(0);
  for (auto& line : norm_density) {
    x_coord = 0;
    for (auto& pixel : line) {
      double red   = -3 * (pixel - 0.75) * (pixel - 0.75) + 1;
      double green = -3 * (pixel - 0.25) * (pixel - 0.25) + 1;
      double blue  = 0;
      red = red > 0 ? red : 0;
      green = green > 0 ? green : 0;
      blue = blue > 0 ? blue : 0;
      unsigned int pixel_R, pixel_G, pixel_B;
      pixel_R = static_cast<unsigned int>(red * 256);
      pixel_G = static_cast<unsigned int>(green * 256);
      pixel_B = static_cast<unsigned int>(blue * 256);
      if (savefig) {
        fout << pixel_R << ' ';
        fout << pixel_G << ' ';
        fout << pixel_B << ' ';
      }
      res(x_coord, y_coord, 0, 0) = pixel_R;
      res(x_coord, y_coord, 0, 1) = pixel_G;
      res(x_coord, y_coord, 0, 2) = pixel_B;
      ++x_coord;
    }
    if (savefig)
      fout << '\n';
    ++y_coord;
  }

  fout << std::flush;
  fout.close();

  return res;
}

cimg_library::CImg<unsigned int> output::display(
        std::vector<std::vector<double>> density,
        std::vector<std::vector<bool>> map, bool savefig,
        const std::string filename) {
  std::ofstream fout(filename);
  auto norm_density = (density-min2d(density))/max2d(density);
  int size_x = norm_density[0].size();
  int size_y = norm_density.size();

  if (savefig) {
    fout << "P3\n";
    fout << norm_density[0].size() << ' ' << norm_density.size() << '\n';
    fout << "255\n";
  }

  auto line1 = norm_density.begin();
  auto line2 = map.begin();
  int x_coord = 0, y_coord = 0;
  cimg_library::CImg<unsigned int> res(size_x, size_y, 1, 3);
  res.fill(0);
  for ( ; line1 != norm_density.end() && line2 != map.end();
          ++line1, ++line2) {
    auto pixel = line1->begin();
    auto terrain = line2->begin();
    x_coord = 0;
    for ( ; pixel != line1->end() && terrain != line2->end();
            ++pixel, ++terrain) {
      unsigned int pixel_R, pixel_G, pixel_B;
      if (*terrain) {
        double red   = -3 * (*pixel - 0.75) * (*pixel - 0.75) + 1;
        double green = -3 * (*pixel - 0.25)* (*pixel - 0.25)  + 1;
        double blue  = 0;
        red = red > 0 ? red : 0;
        green = green > 0 ? green : 0;
        blue = blue > 0 ? blue : 0;
        pixel_R = static_cast<unsigned int>(red * 256);
        pixel_G = static_cast<unsigned int>(green * 256);
        pixel_B = static_cast<unsigned int>(blue * 256);
      } else {
        pixel_R = 10;
        pixel_G = 77;
        pixel_B = 204;
      }
      if (savefig) {
        fout << pixel_R << ' ';
        fout << pixel_G << ' ';
        fout << pixel_B << ' ';
      }
      res(x_coord, y_coord, 0, 0) = pixel_R;
      res(x_coord, y_coord, 0, 1) = pixel_G;
      res(x_coord, y_coord, 0, 2) = pixel_B;
      ++x_coord;
    }
    if (savefig)
      fout << '\n';
    ++y_coord;
  }
  fout << std::flush;
  fout.close();
  return res;
}
