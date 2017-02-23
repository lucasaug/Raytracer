/***************************************
 *                                     *
 * Definition of the RayTracer class   *
 *                                     *
 * Traces the rays for intersections   *
 *                                     *
 ***************************************/

#include <cmath>

#include "../headers/core.hpp"
#include "../headers/mesh.hpp"
#include "../headers/rendering.hpp"

void RayTracer::addObject(GeometricPrimitive obj) {
    this->objects.push_back(obj);
}
void RayTracer::trace(Ray& ray, Vector* color) {
    float hitPos = -1;
    float thit;
    Intersection currentInt;
    Intersection intersect;
    for(GeometricPrimitive obj : this->objects) {
        if(obj.intersect(ray, &thit, &intersect) && (hitPos == -1 || thit < hitPos)) {
            hitPos = thit;
            currentInt = intersect;
        }
    }
    if(hitPos >= 0.0001) {
        (*color) = (currentInt.primitive->material.ka + currentInt.primitive->material.ke) * 255;
        color->x > 255 ? 255 : color->x;
        color->y > 255 ? 255 : color->y;
        color->z > 255 ? 255 : color->z;
    } else {
        color->x = color->y = color->z = 0;
    }
}
