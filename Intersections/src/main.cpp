//
// Created by nixtaxe on 01.03.2018.
//

#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#define EPS 2e-16

#include <cmath>
#include "catch.h"
#include "GeometricFigures.h"

TEST_CASE("Circle tests", "[]") {
  SECTION("Check circle length") {
    Circle c1((Point){.x = 0, .y = 0}, 1);
    REQUIRE(c1.length() == 2.0 * M_PI);
  }
  SECTION("Check circle-circle intersection") {
    WHEN("Circles have two intersection points") {
      Circle c1((Point){.x = 0, .y = 0}, 1);
      Circle c2((Point){.x = 1, .y = 0}, 1);

      THEN("Return vector with two points") {
        vector <Point> result = c1.intersect(c2);
        REQUIRE (abs(result[0].x - 0.5) < EPS);
        REQUIRE (abs(result[1].x - 0.5) < EPS);
      }
    }
  }
}