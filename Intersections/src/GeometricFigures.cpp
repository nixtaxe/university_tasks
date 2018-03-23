//
// Created by nixtaxe on 28.02.2018.
//

#define _USE_MATH_DEFINES
#define EPS 2-16

#include "GeometricFigures.h"

#include <cmath>

using namespace std;

Circle::Circle( const Point& center, const double& radius )
  : center_( center ), radius_( radius )
{
  ;
}

Circle::~Circle() = default
{
  ;
}

Point
Circle::getCenter() const
{
  return this->center_;
}

double
Circle::getRadius() const
{
  return this->radius_;
}

double
Circle::length()
{
  return 2.0 * M_PI * this->getRadius();
}

vector<Point>
Circle::intersect( GeometricFigure& geometricFigure )
{
  return geometricFigure.intersect( *this );
}

vector<Point>
Circle::intersect( Line& line )
{
  //...
}

vector<Point>
Circle::intersect( Circle& circle )
{
  Point c1 = this->getCenter();
  Point c2 = circle.getCenter();

  double dist = sqrt( pow( c1.x - c2.x, 2.0 ) + pow( c1.y - c2.y, 2.0 ));
  double r1 = this->getRadius();
  double r2 = circle.getRadius();
  double maxR = max( r1, r2 );
  double minR = min( r1, r2 );

  bool isTooFar = dist >= (maxR + minR);
  bool isOneInsideAnother = maxR >= (dist + minR);
  bool isEqual = dist < EPS && (maxR - minR) < EPS;
  if (isTooFar || isOneInsideAnother || isEqual)
    return vector<Point> {};

  //http://algolist.manual.ru/maths/geom/intersect/circlecircle2d.php
  double a = (pow( r1, 2.0 ) - pow( r2, 2.0 ) + pow( dist, 2.0 )) / (2.0 * dist);
  double h = sqrt( pow( r1, 2.0 ) - pow( a, 2.0 ));

  double xh = c1.x + a * (c2.x - c1.x) / dist;
  double yh = c1.y + a * (c2.y - c1.y) / dist;

  double deltaX = h * (c2.y - c1.y) / dist;
  double deltaY = h * (c2.x - c1.x) / dist;
  double x1 = xh + deltaX;
  double y1 = yh - deltaY;
  double x2 = xh - deltaX;
  double y2 = yh + deltaY;

  return vector<Point> {{x1, y1}, {x2, y2}};
}

vector<Point>
Circle::intersect( Multiline& multiLine )
{
  //...
}