/****************************************************
 * Classes closely tied to the rendering process    *
 *                                                  *
 * Sampler                                          *
 * Camera                                           *
 * RayTracer                                        *
 * Film                                             *
 * Scene                                            *
 *                                                  *
 ****************************************************/

#ifndef LAFO_RAYTRACER_RENDER

#define LAFO_RAYTRACER_RENDER

#include "core.hpp"

class Sampler {
    private:

    Vector currentPixel;
    Vector screenSize;

    public:

    Sampler(int, int);

    bool getSample(Sample*);
};

class Camera {
    public:

    Vector pos, lookDir, upDir, rightDir;
    float width, height, fovy;

    Camera(Vector, Vector, Vector, float, float, float);

    void generateRay(Sample& sample, Ray* ray);
};

#endif
