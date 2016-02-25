/* Parses the file for instructions, setting the scene accordingly */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>

#include "../headers/core.hpp"
#include "../headers/mesh.hpp"
#include "../headers/rendering.hpp"
#include "../headers/readfile.hpp"

// degrees to radians macro definition
#define radians(x) (x * M_PI  / 180)

using namespace std;

void readFile(string inFileName, Scene& scene) {    
    string str, cmd;
    ifstream inFile;
    inFile.open(inFileName);

    if (inFile.is_open()) {

        // Matrix to store transformations
        stack<Matrix> transfStack;
        stack<Matrix> invTransfStack; // We also store the inverse transformations
        transfStack.push(Matrix()); // Stores the identity
        invTransfStack.push(Matrix());

        // Vector to store triangle vertices
        vector<Vector> vertices;

        // Material properties
        Vector diffuse, specular, emission;
        float shininess = 1;

        // Light properties
        Vector attenuation(1, 0, 0); // Default light attenuation
        Vector ambient(0.2, 0.2, 0.2); // Default ambient lighting

        getline(inFile, str); 
        while (inFile) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines 

                stringstream s(str);
                s >> cmd;

                // General
                if (cmd == "size") {
                    int width, height;
                    s >> width >> height;
                    scene.setViewport(width, height);
                } else if(cmd == "maxdepth") {
                    int depth;
                    s >> depth;
                    scene.setDepth(depth);
                } else if(cmd == "output") {
                    string name;
                    s >> name;
                    scene.setOutputName(name);


                // Camera
                } else if(cmd == "camera") {
                    Vector eye, lookAt, up;
                    float fovy;

                    s >> eye.x >> eye.y >> eye.z;
                    s >> lookAt.x >> lookAt.y >> lookAt.z;
                    s >> up.x >> up.y >> up.z;
                    s >> fovy;

                    scene.setCamera(eye, lookAt, up, radians(fovy));

                // Geometry
                } else if(cmd == "sphere") {
                    Vector center;
                    float radius;

                    s >> center.x >> center.y >> center.z;
                    s >> radius;

                    GeometricPrimitive sphere(SPHERE, center, radius);
                    sphere.material.kd        = diffuse;
                    sphere.material.ks        = specular;
                    sphere.material.ke        = emission;
                    sphere.material.ka        = ambient;
                    sphere.material.shininess = shininess;
                    sphere.objToWorld.m    = transfStack.top();
                    sphere.objToWorld.minv = invTransfStack.top();
                    sphere.worldToObj = sphere.objToWorld;
                    sphere.worldToObj.swap();

                    scene.addObject(sphere);
                } else if(cmd == "vertex") {
                    Vector vertex;
                    s >> vertex.x >> vertex.y >> vertex.z;
                    vertices.push_back(vertex);
                } else if(cmd == "tri") {
                    int indexes[3];

                    s >> indexes[0] >> indexes[1] >> indexes[2];

                    Vector triVertices[3];
                    triVertices[0] = vertices[indexes[0]];
                    triVertices[1] = vertices[indexes[1]];
                    triVertices[2] = vertices[indexes[2]];
                    GeometricPrimitive triangle(TRIANGLE, triVertices);
                    triangle.material.kd        = diffuse;
                    triangle.material.ks        = specular;
                    triangle.material.ke        = emission;
                    triangle.material.ka        = ambient;
                    triangle.material.shininess = shininess;
                    triangle.objToWorld.m    = transfStack.top();
                    triangle.objToWorld.minv = invTransfStack.top();
                    triangle.worldToObj = triangle.objToWorld;
                    triangle.worldToObj.swap();

                    scene.addObject(triangle);

                // Transformations
                } else if(cmd == "translate") {
                    Matrix transl;
                    Vector amount;

                    s >> amount.x >> amount.y >> amount.z;
                    transl.translate(amount);

                    // Multiplies the top of the stack by the translation
                    transfStack.top() = transl * transfStack.top();
                    // and the top of the inverse stack by the inverse translation
                    invTransfStack.top() = invTransfStack.top() * (transl * -1);
                } else if(cmd == "rotate") {
                    Matrix rotation;
                    Vector axis;
                    float amount;

                    s >> axis.x >> axis.y >> axis.z;
                    s >> amount;
                    rotation.rotate(axis, amount);

                    // Multiplies the top of the stack by the rotation
                    transfStack.top() = rotation * transfStack.top();
                    rotation.identity();
                    rotation.rotate(axis, -1 * amount);
                    // Multiplies the top of the inverse stack by the inverse rotation
                    invTransfStack.top() = invTransfStack.top() * rotation;
                } else if(cmd == "scale") {
                    Matrix scale;
                    Vector amount;

                    s >> amount.x >> amount.y >> amount.z;
                    scale.scale(amount);

                    // Multiplies the top of the stack by the scaling
                    transfStack.top() = scale * transfStack.top();
                    scale.identity();
                    amount.x = 1/amount.x;
                    amount.y = 1/amount.y;
                    amount.z = 1/amount.z;
                    scale.scale(amount);
                    // and the top of the inverse stack by the inverse scaling
                    invTransfStack.top() = invTransfStack.top() * scale;
                } else if(cmd == "pushTransform") {
                    transfStack.push(Matrix());
                    invTransfStack.push(Matrix());
                } else if(cmd == "popTransform") {
                    transfStack.pop();
                    invTransfStack.pop();

                // Lights
                } else if(cmd == "directional") {
                } else if(cmd == "point") {
                } else if(cmd == "attenuation") {
                    s >> attenuation.x >> attenuation.y >> attenuation.z;
                } else if(cmd == "ambient") {
                    s >> ambient.x >> ambient.y >> ambient.z;

                // Materials
                } else if(cmd == "diffuse") {
                    s >> diffuse.x >> diffuse.y >> diffuse.z;
                } else if(cmd == "specular") {
                    s >> specular.x >> specular.y >> specular.z;
                } else if(cmd == "emission") {
                    s >> emission.x >> emission.y >> emission.z;
                } else if(cmd == "shininess") {
                    s >> shininess;

                // Ignored or unknown
                } else if(cmd == "maxverts") {
                } else {
                    cout << "Unknown command: " << cmd << "\n";
                }
            }
            getline (inFile, str); 
        }

    } else {
        cerr << "Unable to Open Input Data File " << inFileName << "\n"; 
        throw 2; 
    }
}
