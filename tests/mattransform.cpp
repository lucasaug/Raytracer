#include "../include/catch.hpp"
#include "../headers/core.hpp"

#include <iostream>

/* Unit tests for Matrix and Transformation classes */

TEST_CASE("Matrix and Transformation work as expected") {

    float values1[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    Matrix m1 = Matrix(values1);
    float values2[16] = {17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32};
    Matrix m2 = Matrix(values2);
    Transformation transf;
    Matrix id;

    SECTION("Matrix transposition works") {
        Matrix r = m1;
        r.transpose();
        for (int i = 0; i < 4; i++) {
            for(int j; j < 4; j++) {
                CHECK(r.mat[i][j] == m1.mat[j][i]);
            }
        }
    }

    SECTION("Addition works") {
        Matrix r = m1 + m2;
        int count = 18;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                CHECK(r.mat[i][j] == count);
                count += 2;
            }
        }
    }

    SECTION("Subtraction works") {
        Matrix r = m1 - m2;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                CHECK(r.mat[i][j] == -16);
            }
        }
    }

    SECTION("Scalar multiplication works") {
        Matrix r = m1 * 2;
        int count = 2;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                CHECK(r.mat[i][j] == count);
                count += 2;
            }
        }
    }

    SECTION("Scalar division works") {
        Matrix r = m1 / 2;
        float count = 0.5;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                CHECK(r.mat[i][j] == count);
                count += 0.5;
            }
        }
    }

    SECTION("Matrix multiplication works") {
        Matrix r = m1 * m2;
        float values3[16] = {250,260,270,280,618,644,670,696,986,1028,1070,1112,1354,1412,1470,1528};
        Matrix expected = Matrix(values3);
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                CHECK(r.mat[i][j] == expected.mat[i][j]);
            }
        }
    }

    SECTION("Scaling works") {
        transf.scale(Vector(2,1.5,0.5));
        Matrix prod = transf.minv * transf.m;
        CHECK(prod == id);

        Vector vec = Vector(5,2,9);
        vec = transf * vec;
        CHECK(vec == Vector(10,3,4.5));

        Ray ray = Ray(Vector(1,1,1), Vector(0,1,0));
        ray = transf * ray;
        CHECK(ray.point == Vector(2,1.5,0.5));
        CHECK(ray.dir   == Vector(0, 1.5, 0));

        LocalGeo local = LocalGeo(Vector(1,1,1), Vector(0,1,0));
        local = transf * local;
        CHECK(local.pos    == Vector(2,1.5,0.5));
        CHECK(local.normal == Vector(0,1,0));
    }

    SECTION("Rotation works") {
        transf.rotate(Vector(1,0,0), M_PI_2);
        Matrix prod = transf.minv * transf.m;
        CHECK(prod == id);

        Vector vec = Vector(0,1,0);
        vec = transf * vec;
        CHECK(vec == Vector(0,0,1));

        Ray ray = Ray(Vector(1,0,0), Vector(0,1,0));
        ray = transf * ray;
        CHECK(ray.point == Vector(1,0,0));
        CHECK(ray.dir   == Vector(0,0,1));

        LocalGeo local = LocalGeo(Vector(0,0,1), Vector(0,1,0));
        local = transf * local;
        CHECK(local.pos    == Vector(0,-1,0));
        CHECK(local.normal == Vector(0,0,1));
    }

    SECTION("Translation works") {
        transf.translate(Vector(2,1.5,0.5));
        Matrix prod = transf.minv * transf.m;
        CHECK(prod == id);

        Vector vec = Vector(5,2,9);
        vec = transf * vec;
        CHECK(vec == Vector(7,3.5,9.5));
        std::cout << vec.x << " " << vec.y << " " << vec.z;

        Ray ray = Ray(Vector(1,1,1), Vector(0,1,0));
        ray = transf * ray;
        CHECK(ray.point == Vector(3,2.5,1.5));
        CHECK(ray.dir   == Vector(0,1,0));

        LocalGeo local = LocalGeo(Vector(1,1,1), Vector(0,1,0));
        local = transf * local;
        CHECK(local.pos    == Vector(3,2.5,1.5));
        CHECK(local.normal == Vector(0,1,0));
    }
}
