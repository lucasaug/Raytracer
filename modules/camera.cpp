/************************************************
 *                                              *
 * Definition of the Camera class               *
 *                                              *
 * Produces the correct rays, given the samples *
 *                                              *
 ************************************************/

#include <cmath>

#include "../headers/core.hpp"
#include "../headers/rendering.hpp"

void Camera::setCamera(Vector eye, Vector lookAt, Vector up, int width, int height, float fovy) {
    this->pos = eye;
    this->lookDir = (lookAt - eye).normalize();
    this->rightDir = this->lookDir.cross(up).normalize();
    this->upDir = this->rightDir.cross(this->lookDir).normalize();
    this->width = width;
    this->height = height;
    this->fovy = fovy;
}

void Camera::generateRay(Sample& sample, Ray* ray) {
    float alpha = tan(this->fovy/2.0) * (sample.x - (this->width/2.0)) / (this->width/2.0);
    float beta  = tan(this->fovy/2.0) * ((this->height/2.0) - sample.y) / (this->height/2.0);

    ray->point = this->pos;
    ray->dir   = this->rightDir * alpha + this->upDir * beta + this->lookDir;
    ray->dir.normalize();
}
