//
// Created by nixtaxe on 27.02.2018.
//

#pragma once

#include <vector>
using std::vector;

class GeometricFigure;
class Line;
class Circle;
class Multiline;

struct Point
{
  double x, y;
};


class GeometricFigure
{
public:
  virtual vector<Point>
  intersect( GeometricFigure& ) = 0;

  virtual vector<Point>
  intersect( Line& ) = 0;

  virtual vector<Point>
  intersect( Circle& ) = 0;

  virtual vector<Point>
  intersect( Multiline& ) = 0;

  virtual double
  length() = 0;

  virtual
  ~GeometricFigure() = default;
};


class Circle : public GeometricFigure
{
public:
  vector<Point>
  intersect( GeometricFigure& ) override;

  vector<Point>
  intersect( Line& ) override;

  vector<Point>
  intersect( Circle& ) override;

  vector<Point>
  intersect( Multiline& ) override;

  double
  length();

  Point
  getCenter() const {return center_;};

  double
  getRadius() const {return radius_;};

  Circle( const Point &center, const double &radius )
      : center_ (center), radius_ (radius) {};

  ~Circle() override = default;

private:
  Point center_;
  double radius_;
};


class Line : public GeometricFigure
{
public:
  vector<Point>
  intersect( GeometricFigure& ) override;

  vector<Point>
  intersect( Line& ) override;

  vector<Point>
  intersect( Circle& ) override;

  vector<Point>
  intersect( Multiline& ) override;

  double
  length();

  Line( vector<Point> &points )
      : points_ ( points ) {};

  ~Line() override = default;

private:
  vector<Point> points_;
};


class Multiline : public GeometricFigure
{
public:
  vector<Point>
  intersect( GeometricFigure& ) override;

  vector<Point>
  intersect( Line& ) override;

  vector<Point>
  intersect( Circle& ) override;

  vector<Point>
  intersect( Multiline& ) override;

  double
  length();

  Multiline( vector<Point> &points )
      : points_ ( points ) {};

  ~Multiline() override = default;

private:
  vector<Point> points_;
};
