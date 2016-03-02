#include <iostream>
#include <string>
#include <cmath>

// Module headers
#include "headers/core.hpp"
#include "headers/mesh.hpp"
#include "headers/rendering.hpp"
#include "headers/readfile.hpp"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2) {
        // incorrect number of arguments
        cerr << "No input file name received";
        return 1;
    }

    Scene scene;
    readFile(string(argv[1]), scene);
    
    scene.render();

    return 0;
}

/*
#define WIDTH 250
#define HEIGHT 250
scene.setViewport(WIDTH, HEIGHT);
scene.setCamera(Vector(0,0,0), Vector(0,0,-1), Vector(0,1,0), M_PI/3);
    Vector vertices[3] = {Vector(20,-20,-100), Vector(0,20,-100), Vector(-50,-20,-100)};
    GeometricPrimitive obj = GeometricPrimitive(TRIANGLE, vertices);
    Transformation transf = Transformation();
    transf.translate(Vector(1,0,0));
    obj.objToWorld.m = transf.m;
    obj.objToWorld.minv = transf.minv;
    obj.worldToObj.minv = transf.m;
    obj.worldToObj.m = transf.minv;
    scene.addObject(obj);
    GeometricPrimitive obj2 = GeometricPrimitive(SPHERE, Vector(30,0, -50), 20);
    scene.addObject(obj2);*/