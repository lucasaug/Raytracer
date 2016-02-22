#include "../include/catch.hpp"
#include "../headers/core.hpp"
#include "../headers/rendering.hpp"

#define WIDTH 10
#define HEIGHT 10

/* Unit tests for Sampler class */

TEST_CASE("Sampler works as expected") {

    Sampler smp = Sampler(WIDTH, HEIGHT);

    SECTION("Samples are correct") {
        Sample s;
        Sample expected = Sample(0.5, 0.5);

        while(smp.getSample(&s)) {
            CHECK(s.x == expected.x);
            CHECK(s.y == expected.y);
            expected.x += 1;
            if(expected.x > WIDTH) {
                expected.x = 0.5;
                expected.y += 1;
            }
        }
        CHECK(s.x == 0.5);
        CHECK(s.y == HEIGHT + 0.5);
    }
}
