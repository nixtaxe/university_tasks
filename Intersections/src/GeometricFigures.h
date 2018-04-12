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

bool operator <(const Point& a, const Point& b);

class GeometricFigure
{
public:
  virtual
  ~GeometricFigure() = default;

  virtual double
  length() const = 0;

  virtual vector <Point>
  intersect(const GeometricFigure&) const = 0;

  virtual vector <Point>
  intersect(const Line&) const = 0;

  virtual vector <Point>
  intersect(const Circle&) const = 0;

  virtual vector <Point>
  intersect(const Multiline&) const = 0;
};


class Circle : public GeometricFigure
{
public:
  Circle(const Point& center, double radius);

//  ~Circle() override;
//TODO Remove destructors

  Point
  getCenter() const;

  double
  getRadius() const;

  double
  length() const override;

  vector <Point>
  intersect(const GeometricFigure&) const override;

  vector <Point>
  intersect(const Line&) const override;

  vector <Point>
  intersect(const Circle&) const override;

  vector <Point>
  intersect(const Multiline&) const override;

private:
  Point center_;
  double radius_;
};


class Line : public GeometricFigure
{
public:
  Line(const Point& start, const Point& end);

  ~Line() override;

  Point
  getStart() const;

  Point
  getEnd() const;

  double
  length() const override;

  vector <Point>
  intersect(const GeometricFigure&) const override;

  vector <Point>
  intersect(const Line&) const override;

  vector <Point>
  intersect(const Circle&) const override;

  vector <Point>
  intersect(const Multiline&) const override;

private:
  bool
  isPointOnLine(const Point& point, const Line& line) const;

  Point start_, end_;
};


class Multiline : public GeometricFigure
{
public:
  Multiline(const vector <Point>& points);

  ~Multiline() override;

  double
  length() const override;

  vector <Point>
  intersect(const GeometricFigure&) const override;

  vector <Point>
  intersect(const Line&) const override;

  vector <Point>
  intersect(const Circle&) const override;

  vector <Point>
  intersect(const Multiline&) const override;

private:
  vector <Point> points_;
};
