#include <iostream>
#include <string>
#include <cmath>

// Module headers
#include "headers/core.hpp"
#include "headers/mesh.hpp"
#include "headers/rendering.hpp"
#include "headers/readfile.hpp"

using namespace std;

#define WIDTH 100
#define HEIGHT 100

int main() {
    Scene scene;
    GeometricPrimitive obj;
    obj.shape = Shape(SPHERE, Vector(0,0,-10), 2);

    Camera cam(Vector(0,0,0), Vector(0,0,-1), Vector(0,1,0), WIDTH, HEIGHT, M_PI_4);

    scene.addObject(obj);
    scene.render(camera, WIDTH, HEIGHT);

    return 0;
}
