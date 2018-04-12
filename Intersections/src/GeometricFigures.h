//
// Created by nixtaxe on 27.02.2018.
//

#pragma once

#include <vector>

using std::vector;

//TODO поместить Point в namespace figures
struct Point
{
  double x, y;
};

bool
operator<(const Point&, const Point&);

bool
operator==(const Point&, const Point&);

namespace figures
{
  class GeometricFigure;

  class Line;

  class Circle;

  class Polyline;

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
    intersect(const Polyline&) const = 0;
  };


  class Circle : public GeometricFigure
  {
  public:
    Circle(const Point& center, double radius);

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
    intersect(const Polyline&) const override;

  private:
    Point center_;
    double radius_;
  };


  class Line : public GeometricFigure
  {
  public:
    Line(const Point& start, const Point& end);

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
    intersect(const Polyline&) const override;

  private:
    bool
    isPointOnLine(const Point& point, const Line& line) const;

    Point start_, end_;
  };


  class Polyline : public GeometricFigure
  {
  public:
    Polyline(const vector <Point>& points);

    double
    length() const override;

    vector <Point>
    intersect(const GeometricFigure&) const override;

    vector <Point>
    intersect(const Line&) const override;

    vector <Point>
    intersect(const Circle&) const override;

    vector <Point>
    intersect(const Polyline&) const override;

  private:
    vector <Point> points_;
  };
}
