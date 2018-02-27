//
// Created by nixtaxe on 27.02.2018.
//

#ifndef UNIVERSITY_TASKS_GEOMETRICFIGURES_H
#define UNIVERSITY_TASKS_GEOMETRICFIGURES_H

class GeometricFigure;
class Line;
class Circle;
class Polyline;


class GeometricFigure
{
  public:
    virtual vector<double>
    intersect (GeometricFigure &) = 0;

    virtual vector<double>
    intersect (Line &) = 0;

    virtual vector<double>
    intersect (Circle &) = 0;

    virtual vector<double>
    intersect (Polyline &) = 0;

    virtual
    ~GeometricFigure () = 0;

  protected:
    vector<double> points_;
};


class Line : public GeometricFigure
{
  public:
    vector<double>
    intersect (GeometricFigure &) override;

    vector<double>
    intersect (Line &) override;

    vector<double>
    intersect (Circle &) override;

    vector<double>
    intersect (Polyline &) override;

    Line (vector<double> &points);
    ~Line();
};


class Circle : public GeometricFigure
{
  public:
    vector<double>
    intersect (GeometricFigure &) override;

    vector<double>
    intersect (Line &) override;

    vector<double>
    intersect (Circle &) override;

    vector<double>
    intersect (Polyline &) override;

    Circle (vector<double> &points);
    ~Circle();
};


class Polyline : public GeometricFigure
{
  public:
    vector<double>
    intersect (GeometricFigure &) override;

    vector<double>
    intersect (Line &) override;

    vector<double>
    intersect (Circle &) override;

    vector<double>
    intersect (Polyline &) override;

    Polyline (vector<double> &points);
    ~Polyline();
};

#endif //UNIVERSITY_TASKS_GEOMETRICFIGURES_H
