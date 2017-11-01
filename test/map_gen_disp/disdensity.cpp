// Copyright [2017] <Mengxuan Zhu>

#include "disdensity.h"
#include "vector_arithmetic.hpp"
#include "vector_maxmin.hpp"
#include <fstream>
#include <vector>

void output::savefig(std::vector<std::vector<double>> density,
        const std::string filename, bool color_toggle) {
  std::ofstream fout(filename);

  auto norm_density = (density-min2d(density))/max2d(density);

  if (color_toggle) {
    fout << "P3";
    fout << norm_density[0].size() << ' ' << norm_density.size() << '\n';
    fout << "255\n";
    for (auto& line : norm_density) {
      for (auto& pixel : line) {
        double red   = -3 * (pixel - 0.75) * (pixel - 0.75) + 1;
        double green = -3 * (pixel - 0.25) * (pixel - 0.25) + 1;
        double blue  = 0; //-12 * (pixel - 0.25) * (pixel - 0.25) + 1;
        red = red > 0 ? red : 0;
        green = green > 0 ? green : 0;
        blue = blue > 0 ? blue : 0;
        int pixel_R = static_cast<int>(red * 256);
        int pixel_G = static_cast<int>(green * 256);
        int pixel_B = static_cast<int>(blue * 256);
        fout << pixel_R << ' ';
        fout << pixel_G << ' ';
        fout << pixel_B << ' ';
      }
      fout << '\n';
    }
  } else {
    fout << "P2\n";
    fout << norm_density[0].size() << ' ' << norm_density.size() << '\n';
    fout << "255\n";
    for (auto& line : norm_density) {
      for (auto& pixel : line) {
        int pixel_grayscale = static_cast<int>(pixel*256);
        fout << pixel_grayscale << ' ';
      }
      fout << '\n';
    }
  }
  fout << std::flush;
  fout.close();
}

void output::savefig(std::vector<std::vector<double>> density,
        std::vector<std::vector<bool>> map,
        const std::string filename, bool color_toggle) {
  std::ofstream fout(filename);
  auto norm_density = (density-min2d(density))/max2d(density);

  if (color_toggle) {
    fout << "P3";
    fout << norm_density[0].size() << ' ' << norm_density.size() << '\n';
    fout << "255\n";
    auto line1 = norm_density.begin();
    auto line2 = map.begin();
    for ( ;line1 != norm_density.end() && line2 != map.end();
            ++line1, ++line2) {
      auto pixel = line1->begin();
      auto terrain = line2->begin();
      for ( ;pixel != line1->end() && terrain != line2->end();
              ++pixel, ++terrain) {
        int pixel_R, pixel_G, pixel_B;
        if (*terrain) {
          double red   = -3 * (*pixel - 0.75) * (*pixel - 0.75) + 1;
          double green = -3 * (*pixel - 0.25)* (*pixel - 0.25)  + 1;
          double blue  = 0;//-12 * (*pixel - 0.25) * (*pixel - 0.25) + 1;
          red = red > 0 ? red : 0;
          green = green > 0 ? green : 0;
          blue = blue > 0 ? blue : 0;
          pixel_R = static_cast<int>(red * 256);
          pixel_G = static_cast<int>(green * 256);
          pixel_B = static_cast<int>(blue * 256);
        } else {
          pixel_R = 10;
          pixel_G = 77;
          pixel_B = 204;
        }
        fout << pixel_R << ' ';
        fout << pixel_G << ' ';
        fout << pixel_B << ' ';
      }
      fout << '\n';
    }
  } else {
    fout << "P2\n";
    fout << norm_density[0].size() << ' ' << norm_density.size() << '\n';
    fout << "255\n";
    for (auto& line : norm_density) {
      for (auto& pixel : line) {
        int pixel_grayscale = static_cast<int>(pixel*256);
        fout << pixel_grayscale << ' ';
      }
      fout << '\n';
    }
  }
  fout << std::flush;
  fout.close();
}
