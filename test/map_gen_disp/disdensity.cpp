#include "disdensity.h"
#include "vector_arithmetic.hpp"
#include "vector_maxmin.hpp"

void output::savefig(std::vector<std::vector<double>> map, const std::string filename, bool color){
  std::ofstream fout(filename);

  if(color){
    fout<<"P3";
    fout<<map[0].size()<<' '<<map.size()<<'\n';
    fout<<"255\n";
    for(auto& line : map){
      for(auto& pixel : line){
        double red   = -12 * (pixel - 0.75) * (pixel - 0.75) + 1;
        double green = -12 * (pixel - 0.5)  * (pixel - 0.5)  + 1;
        double blue  = -12 * (pixel - 0.25) * (pixel - 0.25) + 1;
        red = red > 0 ? red : 0 ;
        green = green > 0 ? green : 0 ;
        blue = blue > 0 ? blue : 0 ;
        int pixel_R = static_cast<int>(red * 256);
        int pixel_G = static_cast<int>(green * 256);
        int pixel_B = static_cast<int>(blue * 256);
        fout<<pixel_R<<' ';
        fout<<pixel_G<<' ';
        fout<<pixel_B<<' ';
      }
      fout<<'\n';
    }

    fout<<std::flush;
    fout.close();
  }
  else{
  fout<<"P2\n";
  fout<<map[0].size()<<' '<<map.size()<<'\n';
  fout<<"255\n";
  for(auto& line : map){
    for(auto& pixel : line){
      int pixel_grayscale = static_cast<int>(pixel*256);
      fout<<pixel_grayscale<<' ';
    }
    fout<<'\n';
  }

  fout<<std::flush;
  fout.close();
  }
}
