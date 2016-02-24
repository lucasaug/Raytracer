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
Shape::Shape() {
    this->type = NONE;
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

            if(x1 < 0 && x2 < 0)
                // object behind camera
                return false;
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
        // checks interception with plane containing the triangle
        Vector normal = (this->properties.vertices[2] - this->properties.vertices[0])
                         .cross(this->properties.vertices[1] - this->properties.vertices[0]);

        if(ray.dir.dot(normal) == 0)
            // normal and ray direction are parallel
            return false;

        float t = (this->properties.vertices[0].dot(normal) - ray.point.dot(normal)) / ray.dir.dot(normal);

        if(t < 0)
            // triangle is behind camera
            return false;

        Vector* vertices = this->properties.vertices;
        hitLocation->pos = ray.point + (ray.dir * t);
        hitLocation->normal = vertices[0].cross(vertices[1]).normalize();

        // checks if the point hit is within the triangle's vertices
        if((vertices[1] - vertices[0]).cross(hitLocation->pos - vertices[0]).dot(hitLocation->normal) >= 0 &&
           (vertices[2] - vertices[1]).cross(hitLocation->pos - vertices[1]).dot(hitLocation->normal) >= 0 &&
           (vertices[0] - vertices[2]).cross(hitLocation->pos - vertices[2]).dot(hitLocation->normal) >= 0   ) {
            return true;
        } else {
            return false;
        }

    } else if(this->type == NONE) {
        return false;
    } else {
        throw std::invalid_argument("Unknown shape type" );
    }
}

// GEOMETRIC PRIMITIVE CLASS
GeometricPrimitive::GeometricPrimitive(ShapeType type, Vector center, float radius) {
    this->shape = Shape(type, center, radius);
}
GeometricPrimitive::GeometricPrimitive(ShapeType type, Vector* vertices) {
    this->shape = Shape(type, vertices);
}

bool GeometricPrimitive::intersect(Ray& ray, float* thit, Intersection* hit) {
    LocalGeo interPoint;
    Ray transfRay = worldToObj * ray;
    if(this->shape.intersect(transfRay, thit, &interPoint)) {
        hit->localGeo  = objToWorld * interPoint;
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
