#include <cmath>

#include "../include/catch.hpp"
#include "../headers/core.hpp"
#include "../headers/rendering.hpp"

#define WIDTH 10
#define HEIGHT 10
#define FOVY M_PI_4

/* Unit tests for Camera class */

TEST_CASE("Camera works as expected") {
    
    // Parameters: eye, lookAt, up, width, height, fovy
    Camera cam = Camera(Vector(0,1,0), Vector(1,0,0), Vector(0,1,0), WIDTH, HEIGHT, FOVY);

    SECTION("Camera properties are correctly set") {
        CHECK(cam.lookDir  == (Vector(1,-1,0)).normalize());
        CHECK(cam.upDir    == (Vector(1,1,0) ).normalize());
        CHECK(cam.rightDir ==  Vector(0,0,1));
    }
}
