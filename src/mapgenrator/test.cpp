#include "noise.h"
#include "randommap.h"
#include <vector>
#include <iostream>
#include <fstream>

int main(){

  auto map = setmap(24,24,1.7,1);
  std::ofstream fout("show.py");

  fout<<"import matplotlib.pyplot as plt\n";
  fout<<"import numpy as np\n";
  fout<<"randmap = np.array("<<map<<")\n";
  fout<<"plt.figure()\n";
  fout<<"plt.imshow(randmap,cmap=plt.cm.YlGn)\n";
  fout<<"plt.show()\n";

  fout<<std::flush;
  fout.close();


  return 0;
}

