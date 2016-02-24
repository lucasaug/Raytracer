#include <iostream>
#include <string>
#include <cmath>

// Module headers
#include "headers/core.hpp"
#include "headers/mesh.hpp"
#include "headers/rendering.hpp"
#include "headers/readfile.hpp"

using namespace std;

#define WIDTH 250
#define HEIGHT 250

int main() {
    Scene scene;
    Vector vertices[3] = {Vector(20,-20,-100), Vector(0,20,-100), Vector(-50,-20,-100)};
    GeometricPrimitive obj = GeometricPrimitive(TRIANGLE, vertices);

    Camera cam(Vector(0,0,0), Vector(0,0,-1), Vector(0,1,0), WIDTH, HEIGHT, M_PI/3);

    scene.addObject(&obj);
    GeometricPrimitive obj2 = GeometricPrimitive(SPHERE, Vector(30,0, -50), 20);
    scene.addObject(&obj2);
    scene.render(cam, WIDTH, HEIGHT);

    return 0;
}
