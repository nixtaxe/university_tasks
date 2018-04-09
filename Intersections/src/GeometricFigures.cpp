//
// Created by nixtaxe on 28.02.2018.
//

#define EPS 2e-16

#include "GeometricFigures.h"

#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

bool
operator<(const Point& a, const Point& b)
{
  if (abs( a.x - b.x ) < EPS)
    return a.y > b.y;
  else
    return a.x < b.x;
}

Circle::Circle(const Point& center, double radius)
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
Circle::length() const
{
  return 2.0 * M_PI * radius_;
}

vector <Point>
Circle::intersect(const GeometricFigure& geometricFigure) const
{
  return geometricFigure.intersect( *this );
}

vector <Point>
Circle::intersect(const Line& line) const
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
  bool areIntersectingAtOnePoint = abs( discriminant ) < EPS;

  if (areIntersectingAtOnePoint) {
    double t = -b / (2.0 * a);
    return vector <Point>{{p1.x + t * difP2P1.x, p1.y + t * difP2P1.y}};
  }

  bool areIntersecting = discriminant < 0.0;

  if (areIntersecting) {
    double t1 = (-b + sqrt( discriminant )) / (2.0 * a);
    double t2 = (-b - sqrt( discriminant )) / (2.0 * a);

    vector <Point> result;
    if (t1 >= 0.0 && t1 <= 1.0)
      result.push_back((Point) {p1.x + t1 * difP2P1.x, p1.y + t1 * difP2P1.y} );

    if (t2 >= 0.0 && t2 <= 1.0)
      result.push_back((Point) {p1.x + t2 * difP2P1.x, p1.y + t2 * difP2P1.y} );

    return result;
  }
  else
    return vector <Point>{};
}

vector <Point>
Circle::intersect(const Circle& circle) const
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
    return vector <Point>{};

  //http://algolist.manual.ru/maths/geom/intersect/circlecircle2d.php
  double a = (pow( r1, 2.0 ) - pow( r2, 2.0 ) + pow( dist, 2.0 )) / (2.0 * dist);
  double h = sqrt( pow( r1, 2.0 ) - pow( a, 2.0 ));

  double xh = c1.x + a * (c2.x - c1.x) / dist;
  double yh = c1.y + a * (c2.y - c1.y) / dist;

  double deltaX = h * (c2.y - c1.y) / dist;
  double deltaY = h * (c2.x - c1.x) / dist;
  double x1 = xh + deltaX;
  double y1 = yh - deltaY;

  bool areIntersectingAtOnePoint = abs( h ) < EPS;

  if (areIntersectingAtOnePoint)
    return vector <Point>{(Point) {.x = x1, .y = y1}};

  double x2 = xh - deltaX;
  double y2 = yh + deltaY;

  return vector <Point>{(Point) {.x = x1, .y = y1},
                        (Point) {.x = x2, .y = y2}};
}

vector <Point>
Circle::intersect(const Multiline& multiLine) const
{
  return multiLine.intersect( *this );
}


Line::Line(const Point& start, const Point& end)
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
Line::length() const
{
  return sqrt( pow( start_.x - end_.x, 2.0 ) + pow( start_.y - end_.y, 2.0 ));
}

vector <Point>
Line::intersect(const GeometricFigure& geometricFigure) const
{
  return geometricFigure.intersect( *this );
}

bool
Line::isPointOnLine(const Point& p, const Line& line) const
{
  return p.x >= min( line.getStart().x, line.getEnd().x ) &&
         p.x <= max( line.getStart().x, line.getEnd().x ) &&
         p.y >= min( line.getStart().y, line.getEnd().y ) &&
         p.y <= max( line.getStart().y, line.getEnd().y );
}

vector <Point>
Line::intersect(const Line& line) const
{
  //http://algolist.manual.ru/maths/geom/intersect/lineline2d.php
  Point p1 = this->start_;
  Point p2 = this->end_;
  Point p3 = line.getStart();
  Point p4 = line.getEnd();

  double denominator = ((p4.y - p3.y) * (p2.x - p1.x) -
                        (p4.x - p3.x) * (p2.y - p1.y));

  bool areCollinear = (abs((p2.y - p1.y) * p3.x - (p2.x - p1.x) * p3.y +
                           p2.x * p1.y - p2.y * p1.x ) /
                       this->length()) < EPS;

  bool areParallel = abs( denominator ) < EPS;

  vector <Point> result;
  if (areCollinear) {
    if (isPointOnLine( p1, line ))
      result.push_back( p1 );

    if (isPointOnLine( p2, line ))
      result.push_back( p2 );

    if (isPointOnLine( p3, *this ))
      result.push_back( p3 );

    if (isPointOnLine( p4, *this ))
      result.push_back( p4 );

    return result;
  }
  else if (areParallel)
    return vector <Point>{};

  double u1 = ((p4.x - p3.x) * (p1.y - p3.y) -
               (p4.y - p3.y) * (p1.x - p3.x)) /
              denominator;

  double u2 = ((p2.x - p1.x) * (p1.y - p3.y) -
               (p2.y - p1.y) * (p1.x - p3.x)) /
              denominator;

  bool areIntersecting = u1 >= 0.0 && u1 <= 1.0 && u2 >= 0.0 && u2 <= 1.0;

  if (areIntersecting) {
    Point p = {.x = p1.x + u1 * (p2.x - p1.x),
        .y = p1.y + u1 * (p2.y - p1.y)};
    result.push_back( p );
  }

  return result;
}

vector <Point>
Line::intersect(const Circle& circle) const
{
  return circle.intersect( *this );
}

vector <Point>
Line::intersect(const Multiline& multiline) const
{
  return multiline.intersect( *this );
}


Multiline::Multiline(const vector <Point>& points)
    : points_( points )
{
  ;
}

Multiline::~Multiline() = default;

double
Multiline::length() const
{
  double result = 0.0;
  for (int i = 0; i < points_.size() - 1; ++i) {
    result += Line{points_[i], points_[i + 1]}.length();
  }

  return result;
}

vector <Point>
Multiline::intersect(const GeometricFigure& geometricFigure) const
{
  set <Point> result;
  vector <Point> aVector;
  for (int i = 0; i < this->points_.size() - 1; ++i) {
    Line aLine = Line( this->points_[i], this->points_[i + 1] );
    aVector = aLine.intersect( geometricFigure );
    result.insert( aVector.begin(), aVector.end());
  }

  return vector <Point>{result.begin(), result.end()};
}

vector <Point>
Multiline::intersect(const Line& line) const
{
  set <Point> result;
  vector <Point> aVector;
  for (int i = 0; i < this->points_.size() - 1; ++i) {
    Line aLine = Line( this->points_[i], this->points_[i + 1] );
    aVector = aLine.intersect( line );
    result.insert( aVector.begin(), aVector.end());
  }

  return vector <Point>{result.begin(), result.end()};
}

vector <Point>
Multiline::intersect(const Circle& circle) const
{
  return this->intersect((GeometricFigure&) circle );
}

vector <Point>
Multiline::intersect(const Multiline& multiline) const
{
  return this->intersect((GeometricFigure&) multiline );
}