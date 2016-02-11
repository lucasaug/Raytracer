#include "../headers/core.hpp"
#include <cmath>

using namespace std;

// VECTOR CLASS
Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector Vector::operator+ (const Vector& op) {
    return Vector(this->x + op.x, this->y + op.y, this->z + op.z);
}
Vector Vector::operator- (const Vector& op) {
    return Vector(this->x - op.x, this->y - op.y, this->z - op.z);
}
Vector Vector::operator* (const float& x) {
    return Vector(this->x * x, this->y * x, this->z * x);
}
Vector Vector::operator/ (const float& x) {
    return Vector(this->x / x, this->y / x, this->z / x);
}


Vector Vector::normalize(void) {
    return this->getLength() != 0 ? *(this) / this->getLength() : Vector(0.0, 0.0, 0.0);
}
float Vector::getLength() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}
