//
// Created by nixtaxe on 28.02.2018.
//

#include "GeometricFigures.h"

#include <cmath>
#include <algorithm>

using namespace std;

Circle :: Circle (Point& center, double& radius)
  : center_ (center), radius_ (radius)
{}

Circle :: ~Circle ()
{}

vector<Point>
Circle :: intersect (Circle& circle)
{
  Point c1 = this.getCenter();
  Point c2 = circle.getCenter();

  double dist = sqrt((c1.x - c2.x) * (c1.x - c2.x) + 
                       (c1.y - c2.y) * (c1.y - c2.y));
  double maxR = max(this.getRadius(), circle.getRadius());
  double minR = min(this.getRadius(), circle.getRadius());

  if (dist >= (maxR + minR) || ((maxR >= (dist + minR))))
    return NULL;
  
  double x = (dist * dist - minR * minR + maxR * maxR) /
                (2.0 * dist);

  double y = sqrt((-dist + minR - maxR) * (-dist - minR + maxR) *
                    (-dist + minR + maxR) * (dist + minR + maxR)) /
                      (2.0 * dist);

  return vector<Point> {{min(c1.x, c2.x) + x, c1.y + y},
                          {min(c1.x, c2.x) + x, c1.y - y}};
}