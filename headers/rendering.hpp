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
    int width, height;
    float fovy;

    void setCamera(Vector, Vector, Vector, int, int, float);
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
    Camera camera;
    int width, height;
    int depth;
    std::string outputName;

    Scene();

    void setDepth(int);
    void setOutputName(std::string);
    void setViewport(int, int);
    void setCamera(Vector, Vector, Vector, float);
    void addObject(GeometricPrimitive);
    void render();
};

#endif
