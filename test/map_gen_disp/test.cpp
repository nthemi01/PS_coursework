#include "noise.h"
#include "randommap.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "disdensity.h"

int main(){

  auto map = setmap(40,40,1.7,10,4);
  output::savefig(map, "test.ppm", true);
  return 0;
}

