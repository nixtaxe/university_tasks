//
// Created by nixtaxe on 01.03.2018.
//

#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
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
        REQUIRE ( abs( result[0].x - 1 / sqrt( 2.0 ) ) < EPS );
        REQUIRE ( abs( result[0].x - 1 / sqrt( 2.0 ) ) < EPS );
      }
    }
  }

  SECTION( "Check circle-line intersection" ) {
    WHEN ( "Circle intersects line in two points" ) {
      Circle c((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 2.0},
                (Point) {.x = 2.0, .y = -1.0} );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = c.intersect( line );
        REQUIRE( result.size() == 2 );
        REQUIRE( abs( result[1].x ) < EPS );
        REQUIRE( abs( result[1].y - 1.0) < EPS );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Circle intersects line in one point" ) {
      Circle c((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 2.0, .y = 0.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = c.intersect( line );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Line touches a circle" ) {
      Circle c((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return one point" ) {
        vector<Point> result = c.intersect( line );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x ) < EPS );
        REQUIRE( abs( result[0].y -1.0 ) < EPS );
      }
    }

    WHEN ( "No intersection" ) {
      Circle c((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return empty vector" ) {
        vector<Point> result = c.intersect( line );
        REQUIRE( result.size() == 0 );
      }
    }
  }
}

TEST_CASE( "Line tests", "[]" ) {
  SECTION( "Check line length" ) {
    Line line((Point) {.x = 0.0, .y = 0.0},
              (Point) {.x = 1.0, .y = 0.0} );
    REQUIRE( abs(line.length() - 1.0) < EPS );
  }

  SECTION( "Check line-circle intersection" ) {
    WHEN ( "Line intersects circle in two points" ) {
      Circle c((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 2.0},
                (Point) {.x = 2.0, .y = -1.0} );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = line.intersect( c );
        REQUIRE( result.size() == 2 );
        REQUIRE( abs( result[1].x ) < EPS );
        REQUIRE( abs( result[1].y - 1.0) < EPS );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Line intersects circle in one point" ) {
      Circle c((Point) {.x = 0.0, .y = 0.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 2.0, .y = 0.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = line.intersect( c );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x - 1.0 ) < EPS );
        REQUIRE( abs( result[0].y ) < EPS );
      }
    }

    WHEN ( "Line touches a circle" ) {
      Circle c((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = 0.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return vector with one point" ) {
        vector<Point> result = line.intersect( c );
        REQUIRE( result.size() == 1 );
        REQUIRE( abs( result[0].x ) < EPS );
        REQUIRE( abs( result[0].y -1.0 ) < EPS );
      }
    }

    WHEN ( "No intersection" ) {
      Circle c((Point) {.x = 1.0, .y = 1.0}, 1.0 );
      Line line((Point) {.x = -1.0, .y = 0.0},
                (Point) {.x = 0.0, .y = 2.0} );

      THEN ( "Return empty vector" ) {
        vector<Point> result = line.intersect( c );
        REQUIRE( result.size() == 0 );
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
        REQUIRE(result.size() == 1);
        REQUIRE(abs( result[0].x ) < EPS);
        REQUIRE(abs ( result[0].y - 1.0 ) < EPS);
      }
    }

    WHEN ( "Lines are collinear and are intersecting" ) {
      Line line1((Point) {.x = 0.0, .y = 0.0},
                 (Point) {.x = 0.0, .y = 2.0} );
      Line line2((Point) {.x = 0.0, .y = -1.0},
                 (Point) {.x = 0.0, .y = 3.0} );

      THEN ( "Return vector with two points" ) {
        vector<Point> result = line1.intersect( line2 );
        REQUIRE(result.size() == 2);
        REQUIRE(abs( result[0].x ) < EPS);
        REQUIRE(abs( result[1].x ) < EPS);
        REQUIRE(abs ( result[1].y - 2.0 ) < EPS);
        REQUIRE(abs ( result[0].y ) < EPS);
      }
    }
  }
}

TEST_CASE( "Multiline tests", "[]" ) {
  SECTION( "Check multiline length" ) {
    vector<Point> v{(Point) {.x = 0.0, .y = 1.0},
                    (Point) {.x = 1.0, .y = 1.0},
                    (Point) {.x = 1.0, .y = 0.0},
                    (Point) {.x = 0.0, .y = 0.0},
                    (Point) {.x = 0.0, .y = 1.0}};
    Multiline multiline(v);
    REQUIRE(abs( multiline.length() - 4.0 ) < EPS);
  }
}