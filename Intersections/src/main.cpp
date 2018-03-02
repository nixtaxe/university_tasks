//
// Created by nixtaxe on 01.03.2018.
//

#include <iostream>
#include "GeometricFigures.h"

int main(int argc, char* argv[])
{
  Point p = {1.0, 1.0};
  Circle c((Point){.x = 1, .y = 2}, 3);
  cout << c.getRadius ();
  cout << c.getCenter ().x;
  cout << c.getCenter ().y;
  return 0;
}
