//
// Created by nixtaxe on 28.02.2018.
//

#define _USE_MATH_DEFINES
#define EPS 2e-16

#include "GeometricFigures.h"

#include <cmath>
#include <algorithm>

using namespace std;

bool
Point::operator()( Point i, Point j )
{
  if (abs( i.x - j.x ) < EPS)
    return i.y <= j.y;

  if (abs( i.y - j.y ) < EPS)
    return i.x <= j.x;

  if (i.x <= j.x)
    return true;
  else
    return false;
}

Circle::Circle( const Point& center, const double& radius )
  : center_( center ), radius_( radius )
{
  ;
}

Circle::~Circle() = default;

Point
Circle::getCenter() const
{
  return center_;
}

double
Circle::getRadius() const
{
  return radius_;
}

double
Circle::length()
{
  return 2.0 * M_PI * radius_;
}

vector<Point>
Circle::intersect( GeometricFigure& geometricFigure )
{
  return geometricFigure.intersect( *this );
}

vector<Point>
Circle::intersect( Line& line )
{
  //http://forum2007.algolist.ru/showflat.php/Cat/0/Number/4825/Main/4781
  double r = this->radius_;
  Point center = this->center_;

  Point p1 = line.getStart();
  Point p2 = line.getEnd();

  Point difP2P1 = {p2.x - p1.x, p2.y - p1.y};
  Point difP1C = {p1.x - center.x, p1.y - center.y};

  double a = pow( difP2P1.x, 2.0 ) + pow( difP2P1.y, 2.0 );
  double b = 2.0 * ((difP1C.x * difP2P1.x + difP1C.y * difP2P1.y));
  double c = pow( difP1C.x, 2.0 ) + pow( difP1C.y, 2.0 ) - r * r;

  double discriminant = b * b - 4.0 * a * c;
  if (abs( discriminant ) <= EPS) {
    double t = -b / (2.0 * a);
    return vector<Point> {{p1.x + t * difP2P1.x, p1.y + t * difP2P1.y}};
  }
  if (discriminant < 0.0)
    return vector<Point> {};
  else {
    double t1 = (-b + sqrt( discriminant )) / (2.0 * a);
    double t2 = (-b - sqrt( discriminant )) / (2.0 * a);

    if (t2 < 0.0 || t2 > 1.0)
      return vector<Point> {{p1.x + t1 * difP2P1.x, p1.y + t1 * difP2P1.y}};

    if (t1 < 0.0 || t1 > 1.0)
      return vector<Point> {{p1.x + t2 * difP2P1.x, p1.y + t2 * difP2P1.y}};

    return vector<Point> {{p1.x + t1 * difP2P1.x, p1.y + t1 * difP2P1.y},
                          {p1.x + t2 * difP2P1.x, p1.y + t2 * difP2P1.y}};
  }
}

vector<Point>
Circle::intersect( Circle& circle )
{
  Point c1 = this->center_;
  Point c2 = circle.getCenter();

  double dist = sqrt( pow( c1.x - c2.x, 2.0 ) + pow( c1.y - c2.y, 2.0 ));
  double r1 = this->radius_;
  double r2 = circle.getRadius();
  double maxR = max( r1, r2 );
  double minR = min( r1, r2 );

  bool isTooFar = dist > (maxR + minR);
  bool isOneInsideAnother = maxR > (dist + minR);
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

  if (abs( h ) < EPS)
    return vector<Point> {(Point) {.x = x1, .y = y1}};

  double x2 = xh - deltaX;
  double y2 = yh + deltaY;

  return vector<Point> {(Point) {.x = x1, .y = y1},
                        (Point) {.x = x2, .y = y2}};
}

vector<Point>
Circle::intersect( Multiline& multiLine )
{
  multiLine.intersect( *this );
}


Line::Line( const Point& start, const Point& end )
  : start_( start ), end_( end )
{
  ;
}

Line::~Line() = default;

Point
Line::getStart() const
{
  return start_;
}

Point
Line::getEnd() const
{
  return end_;
}

double
Line::length()
{
  return sqrt( pow( start_.x - end_.x, 2.0 ) + pow( start_.y - end_.y, 2.0 ));
}

vector<Point>
Line::intersect( GeometricFigure& geometricFigure )
{
  return geometricFigure.intersect( *this );
}

bool
Line::isPointOnLine( const Point& p, const Line& line ) const
{
  return p.x >= min( line.getStart().x, line.getEnd().x ) &&
         p.x <= max( line.getStart().x, line.getEnd().x ) ||
         p.y >= min( line.getStart().y, line.getEnd().y ) &&
         p.y <= max( line.getStart().y, line.getEnd().y );
}

vector<Point>
Line::intersect( Line& line )
{
  //http://algolist.manual.ru/maths/geom/intersect/lineline2d.php
  Point p1 = this->start_;
  Point p2 = this->end_;
  Point p3 = line.getStart();
  Point p4 = line.getEnd();

  double denominator = ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

  if (abs( denominator ) < EPS) {
    vector<Point> result = {};

    if (isPointOnLine( p1, line ))
      result.emplace_back( p1 );

    if (isPointOnLine( p2, line ))
      result.emplace_back( p2 );

    if (isPointOnLine( p3, *this ))
      result.emplace_back( p3 );

    if (isPointOnLine( p4, *this ))
      result.emplace_back( p4 );

    return result;
  }

  double u1 = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) /
              denominator;

  double u2 = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) /
              denominator;

  if (u1 < 0.0 || u1 > 1.0)
    if (u2 >= 0.0 && u2 <= 1.0)
      return vector<Point> {(Point) {.x = p3.x + u2 * (p4.x - p3.x),
        .y = p3.y + u2 * (p4.y - p3.y)}};
    else
      return vector<Point> {};

  return vector<Point> {(Point) {.x = p1.x + u1 * (p2.x - p1.x),
    .y = p1.y + u1 * (p2.y - p1.y)}};
}

vector<Point>
Line::intersect( Circle& circle )
{
  return circle.intersect( *this );
}

vector<Point>
Line::intersect( Multiline& multiline )
{
  multiline.intersect( *this );
}


Multiline::Multiline( vector<Point>& points )
  : points_( points )
{
  ;
}

Multiline::~Multiline() = default;

double
Multiline::length()
{
  double result = 0.0;
  for (int i = 0; i < points_.size() - 1; ++i) {
    result += Line{points_[i], points_[i + 1]}.length();
  }
  return result;
}

void
Multiline::deleteDuplicatePoints( vector<Point>& vector )
{
  for (int i = 0; i < vector.size() - 1; ++i)
    for (int j = vector.size() - 1; j > i; --j)
      if (abs( vector[i].x - vector[j].x ) < EPS &&
          abs( vector[i].y - vector[j].y ) < EPS)
        vector.erase( vector.begin() + j );
}

vector<Point>
Multiline::intersect( GeometricFigure& geometricFigure )
{
  geometricFigure.intersect( *this );
}

vector<Point>
Multiline::intersect( Line& line )
{
  vector<Point> result = {};
  for (int i = 0; i < this->points_.size(); ++i) {
    vector<Point> tmp = Line( this->points_[i], this->points_[i + 1] ).intersect( line );
    result.insert( result.end(), tmp.begin(), tmp.end());
  }

  deleteDuplicatePoints( result );

  return result;
}

vector<Point>
Multiline::intersect( Circle& circle )
{
  vector<Point> result = {};
  for (int i = 0; i < this->points_.size(); ++i) {
    vector<Point> tmp = Line( this->points_[i], this->points_[i + 1] ).intersect( circle );
    result.insert( result.end(), tmp.begin(), tmp.end());
  }

  deleteDuplicatePoints( result );

  return result;
}

vector<Point>
Multiline::intersect( Multiline& multiline )
{
  vector<Point> result = {};
  for (int i = 0; i < this->points_.size(); ++i) {
    Line( this->points_[i], this->points_[i + 1] ).intersect( multiline );
    vector<Point> tmp = Line( this->points_[i], this->points_[i + 1] ).intersect( multiline );
    result.insert( result.end(), tmp.begin(), tmp.end());
  }

  deleteDuplicatePoints( result );

  return result;
}