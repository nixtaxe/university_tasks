//
// Created by nixtaxe on 01.03.2018.
//

#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES

#include <cmath>
#include "catch.h"
#include "GeometricFigures.h"

TEST_CASE("Circle-circle intersection", "[]") {
    SECTION("Check circle length") {
        Circle c1((Point){.x = 0, .y = 0}, 1);
        REQUIRE(c1.length() == 2.0 * M_PI);
    }
}

//int main(int argc, char* argv[])
//{
//  Point p = {1.0, 1.0};
//  Circle c((Point){.x = 1, .y = 2}, 3);
//  cout << c.getRadius ();
//  cout << c.getCenter ().x;
//  cout << c.getCenter ().y;
//  return 0;
//}
