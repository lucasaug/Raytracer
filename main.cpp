#include <iostream>
#include <string>
#include <cmath>

// Module headers
#include "headers/core.hpp"
#include "headers/mesh.hpp"
#include "headers/rendering.hpp"
#include "headers/readfile.hpp"

using namespace std;

#define WIDTH 500
#define HEIGHT 500

int main() {
    Scene scene;
    GeometricPrimitive obj = GeometricPrimitive(SPHERE, Vector(0,0, -100), 20);

    Camera cam(Vector(0,0,0), Vector(0,0,-1), Vector(0,1,0), WIDTH, HEIGHT, M_PI/3);

    scene.addObject(&obj);
    scene.render(cam, WIDTH, HEIGHT);

    return 0;
}
