#include "../include/catch.hpp"
#include "../headers/core.hpp"

/* Unit tests for Vector class */

TEST_CASE("Vector operations work as expected") {

    Vector v = Vector(1, 1, 1);

    REQUIRE(v.x == 1);
    REQUIRE(v.y == 1);
    REQUIRE(v.z == 1);

    SECTION("Addition works") {
        v = v + Vector(2,3,4);
        REQUIRE(v.x == 3);
        REQUIRE(v.y == 4);
        REQUIRE(v.z == 5);
    }

    SECTION("Subtration works") {
        v = v - Vector(2,3,4);
        REQUIRE(v.x == -1);
        REQUIRE(v.y == -2);
        REQUIRE(v.z == -3);
    }

    SECTION("Scalar multiplication works") {
        v = v * 3;
        REQUIRE(v.x == 3);
        REQUIRE(v.y == 3);
        REQUIRE(v.z == 3);
    }

    SECTION("Scalar division works") {
        v = v / 2;
        REQUIRE(v.x == 0.5);
        REQUIRE(v.y == 0.5);
        REQUIRE(v.z == 0.5);
    }

    SECTION("Normalization works") {
        v = v.normalize();
        REQUIRE(v.x == 1 / sqrt(3));
        REQUIRE(v.y == 1 / sqrt(3));
        REQUIRE(v.z == 1 / sqrt(3));

        v = Vector(0,0,0);
        v = v.normalize();
    }
}
