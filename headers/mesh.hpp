/**********************************************
 * Classes related to materials and shapes    *
 *                                            *
 * Shape                                      *
 * Intersection                               *
 * GeometricPrimitive                         *
 * Light                                      *
 *                                            *
 **********************************************/

#ifndef LAFO_RAYTRACER_MESH

#define LAFO_RAYTRACER_MESH

#include "core.hpp"

class Shape;
class Intersection;
class GeometricPrimitive;
class Light;

enum ShapeType {
    TRIANGLE,
    SPHERE
};

enum LightType {
    POINT,
    DIRECTIONAL
};

// Stores either the sphere or the triangle data
union ShapeProperties {
    struct {
        float x, y, z;
        float radius;
    };
    struct {
        Vector vertices[3];
    };
};

class Shape {
    public:
    ShapeType type;
    ShapeProperties properties;

    Shape(ShapeType, Vector, float);
    Shape(ShapeType, Vector*);

    bool intersect(Ray&, float*, LocalGeo*);
};

class Intersection {
    public:

    LocalGeo localGeo;
    GeometricPrimitive* primitive;

    void operator= (const Intersection&);
};

class GeometricPrimitive {
    public:

    Shape shape;
    BRDF material;
    Transformation objToWorld, worldToObj;

    bool intersect(Ray&, float*, Intersection*);
};

class Light {
    public:

    LightType type;
};

#endif
