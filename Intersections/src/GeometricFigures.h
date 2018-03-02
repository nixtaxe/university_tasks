//
// Created by nixtaxe on 27.02.2018.
//

#ifndef UNIVERSITY_TASKS_GEOMETRICFIGURES_H
#define UNIVERSITY_TASKS_GEOMETRICFIGURES_H

#include <vector>
using namespace std;

class GeometricFigure;
class Line;
class Circle;
class Polyline;


struct Point
{
  double x, y;
};


class GeometricFigure
{
  public:
    virtual vector<Point>
    intersect (GeometricFigure&) = 0;

    virtual vector<Point>
    intersect (Line&) = 0;

    virtual vector<Point>
    intersect (Circle&) = 0;

    virtual vector<Point>
    intersect (Polyline&) = 0;

    virtual
    ~GeometricFigure () = 0;
};


class Circle : public GeometricFigure
{
  public:
    vector<Point>
    intersect (GeometricFigure&) override;

    vector<Point>
    intersect (Line&) override;

    vector<Point>
    intersect (Circle&) override;

    vector<Point>
    intersect (Polyline&) override;

    Point
    getCenter ();

    double
    getRadius ();

    Circle (const Point& center, const double& radius);

    ~Circle () override;

  private:
    Point center_;
    double radius_;
};


class Line : public GeometricFigure
{
  public:
    vector<Point>
    intersect (GeometricFigure&) override;

    vector<Point>
    intersect (Line&) override;

    vector<Point>
    intersect (Circle&) override;

    vector<Point>
    intersect (Polyline&) override;

    Line (const vector<Point>& points);

    ~Line () override;

  private:
    vector<Point> points_;
};


class Polyline : public GeometricFigure
{
  public:
    vector<Point>
    intersect (GeometricFigure&) override;

    vector<Point>
    intersect (Line&) override;

    vector<Point>
    intersect (Circle&) override;

    vector<Point>
    intersect (Polyline&) override;

    Polyline (const vector<Point>& points);

    ~Polyline ();

  private:
    vector<Point> points_;
};

#endif //UNIVERSITY_TASKS_GEOMETRICFIGURES_H
