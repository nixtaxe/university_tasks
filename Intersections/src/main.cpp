//
// Created by nixtaxe on 01.03.2018.
//

#define CATCH_CONFIG_MAIN
#define EPS 2e-16

#include <cmath>
#include "catch.h"
#include "GeometricFigures.h"

TEST_CASE( "Circle tests", "[]" )
{
  SECTION( "Check circle length" ) {
    Circle c1((Point) {.x = 0.0, .y = 0.0}, 1.0 );
    REQUIRE( c1.length() == 2.0 * M_PI );
  }

  SECTION( "Check circle-circle intersection" ) {

    WHEN ( "Circles have two intersection points" ) {
      Circle c1((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Circle c2((Point) {.x = 1.0, .y = 0.0}, 1.0 );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = c1.intersect( c2 );
        REQUIRE( result.size() == 2 );
        REQUIRE ( abs( result[0].x - 0.5 ) < EPS );
        REQUIRE ( abs( result[1].x - 0.5 ) < EPS );
      }
    }

    WHEN ( "Circles have one intersection point" ) {
      Circle c1((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Circle c2((Point) {.x = sqrt( 2.0 ), .y = sqrt( 2.0 )}, 1.0 );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = c1.intersect( c2 );
        REQUIRE( result.size() == 1 );
        REQUIRE ( abs( result[0].x - 1 / sqrt( 2.0 )) < EPS );
        REQUIRE ( abs( result[0].x - 1 / sqrt( 2.0 )) < EPS );
      }
    }

    WHEN ( "Circles have no intersection points" ) {
      Circle c1((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Circle c2((Point) {.x = 3.0, .y = 0.0}, 1.0 );

      THEN ( "Return vector with no points" ) {
        vector<Point> result = c1.intersect( c2 );
        REQUIRE( result.empty() );
      }
    }
  }

  SECTION( "Check circle-line intersection" ) {

    WHEN ( "Circle intersects line in two points" ) {
      Circle circle((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 2.0},
                (Point) {.x = 2.0, .y = -1.0} );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = circle.intersect( line );
        REQUIRE( result.size() == 2 );
        REQUIRE( abs( result[1].x ) < EPS );
        REQUIRE( abs( result[1].y - 1.0 ) < EPS );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Circle intersects line in one point" ) {
      Circle circle((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 2.0, .y = 0.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = circle.intersect( line );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Line touches a circle" ) {
      Circle circle((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return one point" ) {
        vector<Point> result = circle.intersect( line );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x ) < EPS );
        REQUIRE( abs( result[0].y - 1.0 ) < EPS );
      }
    }

    WHEN ( "No intersection" ) {
      Circle circle((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return empty vector" ) {
        vector<Point> result = circle.intersect( line );
        REQUIRE( result.empty() );
      }
    }
  }
}

TEST_CASE( "Line tests", "[]" )
{
  SECTION( "Check line length" ) {
    Line line((Point) {.x = 0.0, .y = 0.0},
              (Point) {.x = 1.0, .y = 0.0} );
    REQUIRE( abs( line.length() - 1.0 ) < EPS );
  }

  SECTION( "Check line-circle intersection" ) {

    WHEN ( "Line intersects circle in two points" ) {
      Circle circle((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 2.0},
                (Point) {.x = 2.0, .y = -1.0} );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = line.intersect( circle );
        REQUIRE( result.size() == 2 );
        REQUIRE( abs( result[1].x ) < EPS );
        REQUIRE( abs( result[1].y - 1.0 ) < EPS );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Line intersects circle in one point" ) {
      Circle circle((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 2.0, .y = 0.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = line.intersect( circle );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Line touches a circle" ) {
      Circle circle((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = line.intersect( circle );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x ) < EPS );
        REQUIRE( abs( result[0].y - 1.0 ) < EPS );
      }
    }

    WHEN ( "No intersection" ) {
      Circle circle((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return empty vector" ) {
        vector<Point> result = line.intersect( circle );
        REQUIRE( result.empty() );
      }
    }
  }

  SECTION ( "Check line-line intersection" ) {

    WHEN ( "Lines are not collinear and are intersecting" ) {
      Line line1((Point) {.x = 0.0, .y = 0.0},
                 (Point) {.x = 0.0, .y = 2.0} );
      Line line2((Point) {.x = -1.0, .y = 1.0},
                 (Point) {.x = 1.0, .y = 1.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = line1.intersect( line2 );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x ) < EPS );
        REQUIRE( abs( result[0].y - 1.0 ) < EPS );
      }
    }

    WHEN ( "Lines are collinear and are intersecting" ) {
      Line line1((Point) {.x = 0.0, .y = 0.0},
                 (Point) {.x = 0.0, .y = 2.0} );
      Line line2((Point) {.x = 0.0, .y = -1.0},
                 (Point) {.x = 0.0, .y = 3.0} );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = line1.intersect( line2 );
        REQUIRE( result.size() == 2 );
        REQUIRE( abs( result[0].x ) < EPS );
        REQUIRE( abs( result[1].x ) < EPS );
        REQUIRE( abs( result[1].y - 2.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Lines are not collinear and are not intersecting" ) {
      Line line1((Point) {.x = 4.0, .y = 0.0},
                 (Point) {.x = 0.0, .y = 2.0} );
      Line line2((Point) {.x = 0.0, .y = 0.0},
                 (Point) {.x = 0.0, .y = 1.0} );

      THEN ( "Return vector with no points" ) {
        vector<Point> result = line1.intersect( line2 );
        REQUIRE( result.empty() );
      }
    }

    WHEN ( "Lines are parallel" ) {
      Line line1((Point) {.x = 0.0, .y = 0.0},
                 (Point) {.x = 0.0, .y = 2.0} );
      Line line2((Point) {.x = 1.0, .y = -1.0},
                 (Point) {.x = 1.0, .y = 3.0} );

      THEN ( "Return vector with no points" ) {
        vector<Point> result = line1.intersect( line2 );
        REQUIRE( result.empty() );
      }
    }
  }
}

TEST_CASE( "Multiline tests", "[]" )
{
  SECTION( "Check multiline length" ) {
    vector<Point> v {(Point) {.x = 0.0, .y = 1.0},
                     (Point) {.x = 1.0, .y = 1.0},
                     (Point) {.x = 1.0, .y = 0.0},
                     (Point) {.x = 0.0, .y = 0.0},
                     (Point) {.x = 0.0, .y = 1.0}};
    Multiline multiline( v );
    REQUIRE( abs( multiline.length() - 4.0 ) < EPS );
  }

  SECTION( "Check multiline-line intersection" ) {

    WHEN( "Line intersects multiline in multiple similar points" ) {
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );
      vector<Point> v {(Point) {.x = 0.0, .y = 1.0},
                       (Point) {.x = 1.0, .y = 1.0},
                       (Point) {.x = 0.0, .y = 2.0},
                       (Point) {.x = 0.0, .y = 1.0},
                       (Point) {.x = 0.0, .y = 0.0}};
      Multiline multiline( v );

      THEN( "Return vector with original points" ) {
        vector<Point> result = multiline.intersect( line );
        REQUIRE( result.size() == 3 );
      }
    }

    WHEN( "Line is not intersecting multiline" ) {
      Line line((Point) {.x = -1.0, .y = -1.0},
                (Point) {.x = -1.0, .y = 2.0} );
      vector<Point> v {(Point) {.x = 0.0, .y = 1.0},
                       (Point) {.x = 1.0, .y = 1.0},
                       (Point) {.x = 0.0, .y = 2.0},
                       (Point) {.x = 0.0, .y = 1.0},
                       (Point) {.x = 0.0, .y = 0.0}};
      Multiline multiline( v );

      THEN( "Return vector no points" ) {
        vector<Point> result = multiline.intersect( line );
        REQUIRE( result.empty() );
      }
    }
  }

  SECTION( "Check multiline-multiline intersection" ) {

    WHEN( "Multiline intersects multiline in one point" ) {
      vector<Point> v1 {(Point) {.x = 0.0, .y = 1.0},
                        (Point) {.x = 1.0, .y = 1.0}};
      Multiline multiline1( v1 );
      vector<Point> v2 {(Point) {.x = 0.5, .y = 2.0},
                        (Point) {.x = 0.5, .y = 0.5}};
      Multiline multiline2( v2 );

      THEN( "Return vector with one point" ) {
        vector<Point> result = multiline1.intersect( multiline2 );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x - 0.5 ) < EPS );
        REQUIRE( abs( result[0].y - 1.0 ) < EPS );
      }
    }

    WHEN( "Multiline is not intersecting multiline" ) {
      vector<Point> v1 {(Point) {.x = 1.0, .y = 1.0},
                        (Point) {.x = 2.0, .y = 2.0},
                        (Point) {.x = 3.0, .y = 3.0}};
      Multiline multiline1( v1 );
      vector<Point> v2 {(Point) {.x = 0.5, .y = 1.0},
                        (Point) {.x = 0.5, .y = 0.5},
                        (Point) {.x = 0.5, .y = 0.0}};
      Multiline multiline2( v2 );

      THEN( "Return vector with no points" ) {
        vector<Point> result = multiline1.intersect( multiline2 );
        REQUIRE( result.empty() );
      }
    }
  }

  SECTION( "Check multiline-cirlce intersection" ) {

    WHEN( "Multiline intersects circle in multiple points" ) {
      vector<Point> v1 {(Point) {.x = -1.0, .y = 0.0},
                        (Point) {.x = 0.0, .y = 1.0},
                        (Point) {.x = 1.0, .y = 0.0},
                        (Point) {.x = 0.0, .y = -1.0}};
      Multiline multiline1( v1 );
      Circle circle( (Point) {.x = 0.0, .y = 0.0}, 1.0);

      THEN( "Return vector with one point" ) {
        vector<Point> result = multiline1.intersect( circle );
        REQUIRE( result.size() == 4 );
      }
    }

    WHEN( "Multiline is not intersecting circle" ) {
      vector<Point> v1 {(Point) {.x = 1.0, .y = 1.0},
                        (Point) {.x = 2.0, .y = 2.0},
                        (Point) {.x = 3.0, .y = 3.0}};
      Multiline multiline1( v1 );
      Circle circle( (Point) {.x = -1.0, .y = 0.0}, 1.0 );

      THEN( "Return vector with no points" ) {
        vector<Point> result = multiline1.intersect( circle );
        REQUIRE( result.empty() );
      }
    }
  }
}

TEST_CASE( "Vector of geometric figures tests", "[]" )
{
  SECTION( "Check intersection of vector with circles and vector with lines" ) {
    vector <GeometricFigure*> v1;
    for (double i = 0.0; i <= 6.0; i += 2.0)
      v1.push_back(new Circle((Point){.x = i, .y = 0.0}, 1.0));

    vector <GeometricFigure*> v2;
    for (double i = 0.0; i <= 6.0; i += 2.0)
      v2.push_back(new Line((Point) {.x = i, .y = 0.5},
                            (Point) {.x = i, .y = 1.0}));

    vector<Point> result;
    vector<Point> aVector;
    for (auto i = 0; i < v1.size(); ++i)
      for (auto j = 0; j < v2.size(); ++j) {
        aVector = v1[i]->intersect( *v2[j] );
        for (auto it : aVector)
           result.push_back(it);
    }

    REQUIRE( result.size() == 4 );

  }
}