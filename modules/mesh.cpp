/* Definition of the classes related to materials and shapes */

#include <cmath>
#include <stdexcept>

#include "../headers/mesh.hpp"

// SHAPE CLASS
Shape::Shape(ShapeType type, Vector position, float radius) {
    this->type = type;
    this->properties.x = position.x;
    this->properties.y = position.y;
    this->properties.z = position.z;
    this->properties.radius   = radius;
}
Shape::Shape(ShapeType type, Vector* vertices) {
    this->type = type;
    for (int i = 0; i < 3; i++) {
        this->properties.vertices[i] = vertices[i];
    }
}

bool Shape::intersect(Ray& ray, float* thit, LocalGeo* hitLocation) {
    if(this->type == SPHERE) {
        Vector position = Vector(this->properties.x, this->properties.y, this->properties.z);

        // Quadratic equation description
        float a = ray.dir.dot(ray.dir),
              b = 2 * ray.dir.dot(ray.point - position),
              c = (ray.point - position).dot(ray.point - position) - pow(this->properties.radius, 2);

        float delta = pow(b, 2) - 4 * a * c;

        if(delta < 0) {
            // no intersection
            return false;
        } else {
            // intersection
            float x1 = (-1 * b + sqrt(delta)) / (2 * a),
                  x2 = (-1 * b - sqrt(delta)) / (2 * a);

            if(std::min(x1, x2) <= 0 && std::max(x1, x2) >= 0)
                // camera inside sphere
                *thit = std::max(x1,x2);
            else
                // camera outside sphere
                *thit = std::min(x1,x2);

            hitLocation->pos = ray.point + (ray.dir * (*thit));
            hitLocation->normal = (hitLocation->pos - position).normalize();
            return true;
        }
    } else if(this->type == TRIANGLE) {
        return false;
    } else {
        throw std::invalid_argument("Unknown shape type" );
    }
}

// GEOMETRIC PRIMITIVE CLASS
bool GeometricPrimitive::intersect(Ray& ray, float* thit, Intersection* hit) {
    LocalGeo interPoint;
    if(this->shape.intersect(ray, thit, &interPoint)) {
        hit->localGeo  = interPoint;
        hit->primitive = this;
        return true;
    } else {
        return false;
    }
}

// INTERSECTION CLASS
void Intersection::operator= (const Intersection& op) {
    this->localGeo.pos    = op.localGeo.pos;
    this->localGeo.normal = op.localGeo.normal;
    this->primitive       = op.primitive;
}
