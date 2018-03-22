//
// Created by nixtaxe on 28.02.2018.
//

#include "GeometricFigures.h"

#include <cmath>

using namespace figures;
using namespace std;

vector<Point>
Circle :: intersect (GeometricFigure& geometricFigure)
{
  return geometricFigure.intersect(*this);
}

vector<Point>
Circle :: intersect (Line& line)
{
  //...
}

vector<Point>
Circle :: intersect (Circle& circle)
{
  Point c1 = this->getCenter();
  Point c2 = circle.getCenter();

  double dist = sqrt((c1.x - c2.x) * (c1.x - c2.x) + 
                       (c1.y - c2.y) * (c1.y - c2.y));
  double maxR = max(this->getRadius(), circle.getRadius());
  double minR = min(this->getRadius(), circle.getRadius());

  if (dist >= (maxR + minR) || ((maxR >= (dist + minR))))
    return vector<Point> {};
  
  double x = (dist * dist - minR * minR + maxR * maxR) /
                (2.0 * dist);

  double y = sqrt((-dist + minR - maxR) * (-dist - minR + maxR) *
                    (-dist + minR + maxR) * (dist + minR + maxR)) /
                      (2.0 * dist);

  return vector<Point> {{min(c1.x, c2.x) + x, c1.y + y},
                          {min(c1.x, c2.x) + x, c1.y - y}};
}

vector<Point>
Circle :: intersect (Multiline&)
{
  //...
}