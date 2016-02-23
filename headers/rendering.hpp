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

#include <vector>
#include <string>
#include <cstdint>

#include "core.hpp"
#include "mesh.hpp"

typedef unsigned char BYTE; // unsigned char alias

class Sampler;
class Camera;
class RayTracer;
class Film;

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

class RayTracer {
    public:

    std::vector<GeometricPrimitive> objects;

    void addObject(GeometricPrimitive);

    void trace(Ray&, Vector*);
};

class Film {
    public:

    BYTE* pixels;
    int width, height;

    Film(int, int);

    void commit(Sample&, Vector&);
    void writeImage(std::string);
    void cleanUp();
};

class Scene {
    public:
    RayTracer tracer;

    void addObject(GeometricPrimitive);
    void render(Camera, int, int);
};

#endif
