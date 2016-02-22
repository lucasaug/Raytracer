/************************************************
 * Definition of the Camera class               *
 *                                              *
 * Produces the correct rays, given the samples *
 *                                              *
 ************************************************/

#include "../headers/core.hpp"
#include "../headers/rendering.hpp"

Camera::Camera(Vector eye, Vector lookAt, Vector up, float fovy) {
    this->pos = eye;
    this->lookDir = (lookAt - eye).normalize();
    this->upDir = this->lookDir.cross(up).cross(this->lookDir).normalize();
    this->fovy = fovy;
}

void generateRay(Sample& sample, Ray* ray) {
    
}
