#include "../include/catch.hpp"
#include "../headers/core.hpp"

/* Unit tests for Vector class */

TEST_CASE("Vector operations work as expected") {

    Vector v = Vector(1, 1, 1);

    REQUIRE(v.x == 1);
    REQUIRE(v.y == 1);
    REQUIRE(v.z == 1);

    SECTION("Equality and inequality works") {
        CHECK(v == Vector(1, 1, 1));
        CHECK(v != Vector(1, 1, 8));
    }

    SECTION("Addition works") {
        v = v + Vector(2, 3, 4);
        CHECK(v.x == 3);
        CHECK(v.y == 4);
        CHECK(v.z == 5);
    }

    SECTION("Subtration works") {
        v = v - Vector(2, 3, 4);
        CHECK(v.x == -1);
        CHECK(v.y == -2);
        CHECK(v.z == -3);
    }

    SECTION("Scalar multiplication works") {
        v = v * 3;
        CHECK(v.x == 3);
        CHECK(v.y == 3);
        CHECK(v.z == 3);
    }

    SECTION("Scalar division works") {
        v = v / 2;
        CHECK(v.x == 0.5);
        CHECK(v.y == 0.5);
        CHECK(v.z == 0.5);
    }

    SECTION("Normalization works") {
        v.normalize();
        CHECK(v.x == (1 / (float)sqrt(3)) );
        CHECK(v.y == (1 / (float)sqrt(3)) );
        CHECK(v.z == (1 / (float)sqrt(3)) );

        v = Vector(0, 0, 0);
        CHECK_NOTHROW(v.normalize());
        CHECK(v.x == 0);
        CHECK(v.y == 0);
        CHECK(v.z == 0);
    }

    SECTION("Dot and cross products work") {
        float dotResult = v.dot(Vector(2,3,4));
        CHECK(dotResult == 9);

        v.x = 1;
        v.y = 0;
        v.z = 0;
        Vector crossResult = v.cross(Vector(0,0,1));
        CHECK(crossResult == Vector(0,-1,0));
    }
}
