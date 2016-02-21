#include "../headers/core.hpp"
#include <cmath>

#define RT_EPSILON 0.0001

using namespace std;

// VECTOR CLASS
Vector::Vector() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

bool Vector::operator== (const Vector& op) {
    return (this->x <= op.x + RT_EPSILON && this->x >= op.x - RT_EPSILON) && 
           (this->y <= op.y + RT_EPSILON && this->y >= op.y - RT_EPSILON) &&
           (this->z <= op.z + RT_EPSILON && this->z >= op.z - RT_EPSILON);
}
bool Vector::operator!= (const Vector& op) {
    return !(*(this) == op);
}
void Vector::operator= (const Vector& op) {
    this->x = op.x;
    this->y = op.y;
    this->z = op.z;
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
float& Vector::operator[] (int i) {
    if     (i == 0) return this->x;
    else if(i == 1) return this->y;
    return this->z;
}

void Vector::normalize(void) {
    if(this->getLength() != 0) {
        float len = this->getLength();
        this->x /= len;
        this->y /= len;
        this->z /= len;
    }
}
float Vector::getLength() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

// RAY CLASS
Ray::Ray() {
    this->point = Vector();
    this->dir   = Vector();
}
Ray::Ray(const Vector& point, const Vector& dir) {
    this->point = point;
    this->dir   = dir;
}

// LOCALGEO CLASS
LocalGeo::LocalGeo() {
    this->pos.x = this->pos.y = this->pos.z = 0;
    this->normal.x = this->normal.y = this->normal.z = 0;
    this->normal.normalize();
}
LocalGeo::LocalGeo(Vector position, Vector norm) {
    this->pos = position;
    this->normal = norm;
    this->normal.normalize();
}

// MATRIX CLASS
Matrix::Matrix() {
    this->identity();
}
Matrix::Matrix(float values[16]) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            mat[i][j] = values[i * 4 + j];
        }
    }
}

void Matrix::identity() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            this->mat[i][j] = 0;
        }
    }
    this->mat[0][0] = 1;
    this->mat[1][1] = 1;
    this->mat[2][2] = 1;
    this->mat[3][3] = 1;
}
void Matrix::transpose() {
    Matrix res;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            res.mat[i][j] = this->mat[j][i];
        }
    }
    *(this) = res;
}
void Matrix::scale(Vector amount) {
    this->identity();
    this->mat[0][0] = amount.x;
    this->mat[1][1] = amount.y;
    this->mat[2][2] = amount.z;
}
void Matrix::rotate(Vector axis, float theta) {
    this->identity();
    Matrix first, second, third;
    first.mat[3][3] = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            second.mat[i][j] = axis[i] * axis[j];
        }
    }
    second.mat[3][3] = 0;
    third.mat[0][0] = third.mat[1][1] = third.mat[2][2] = third.mat[3][3] = 0;
    third.mat[0][1] = -1 * axis.z;
    third.mat[0][2] = axis.y;
    third.mat[1][2] = -1 * axis.x;
    third.mat[1][0] = axis.z;
    third.mat[2][0] = -1 * axis.y;
    third.mat[2][1] = axis.x;

    *(this) = first * cos(theta) + second * (1 - cos(theta)) + third * (sin(theta));
    (*this).mat[3][3] = 1;
}
void Matrix::translate(Vector amount) {
    this->identity();
    this->mat[0][3] = amount.x;
    this->mat[1][3] = amount.y;
    this->mat[2][3] = amount.z;
}

bool Matrix::operator== (const Matrix& cmp){
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if((this->mat[i][j] > cmp.mat[i][j] + RT_EPSILON) || (this->mat[i][j] < cmp.mat[i][j] - RT_EPSILON))
                return false;
        }
    }
    return true;
}
bool Matrix::operator!= (const Matrix& cmp){
    return !(*(this) == cmp);
}
Matrix Matrix::operator+ (const Matrix& op) {
    Matrix result;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            result.mat[i][j] = this->mat[i][j] + op.mat[i][j];
        }
    }
    return result;
}
Matrix Matrix::operator- (const Matrix& op) {
    Matrix result;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            result.mat[i][j] = this->mat[i][j] - op.mat[i][j];
        }
    }
    return result;
}
void Matrix::operator= (const Matrix& op) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            this->mat[i][j] = op.mat[i][j];
        }
    }
}
Matrix Matrix::operator* (const Matrix& op) {
    Matrix res;
    res.mat[0][0] = res.mat[1][1] = res.mat[2][2] = res.mat[3][3] = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            for(int k = 0; k < 4; k++) {
                res.mat[i][j] += (*this).mat[i][k] * op.mat[k][j];
            }
        }
    }
    return res;
}
Matrix Matrix::operator* (float op) {
    Matrix result;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            result.mat[i][j] = this->mat[i][j]  * op;
        }
    }
    return result;
}
Matrix Matrix::operator/ (float op) {
    return *(this) * (1.0/op);
}

// TRANSFORMATION CLASS
Transformation::Transformation() {
    this->reset();
}

void Transformation::reset() {
    this->m.identity();
    this->minv.identity();
}
void Transformation::swap() {
    Matrix aux = this->m;
    this->m = this->minv;
    this->minv = aux;
}
void Transformation::scale(Vector amount) {
    Matrix transf;
    transf.scale(amount);
    this->m = transf * this->m;
    transf.identity();
    amount.x = 1 / amount.x;
    amount.y = 1 / amount.y;
    amount.z = 1 / amount.z;
    transf.scale(amount);
    this->minv = this->minv * transf;
}
void Transformation::rotate(Vector axis, float theta) {
    Matrix transf;
    transf.rotate(axis, theta);
    this->m = transf * this->m;
    transf.identity();
    transf.rotate(axis, -1 * theta);
    this->minv = this->minv * transf;
}
void Transformation::translate(Vector amount) {
    Matrix transf;
    transf.translate(amount);
    this->m = transf * this->m;
    transf.identity();
    transf.translate(amount * -1);
    this->minv = this->minv * transf;
}

Vector Transformation::operator* (Vector& vec) {
    Vector result;
    for(int i = 0; i < 3; i++) {
        result[i] = this->m.mat[i][3]/this->m.mat[3][3];
        for(int j = 0; j < 3; j++) {
            result[i] += this->m.mat[i][j] * vec[j];
        }
    }
    return result;
}
Ray Transformation::operator* (Ray& ray) {
    Ray result;
    result.point = *(this) * ray.point;
    Vector dir;
    for(int i = 0; i < 3; i++) {
        dir[i] = 0;
        for(int j = 0; j < 3; j++) {
            dir[i] += this->m.mat[i][j] * ray.dir[j];
        }
    }
    result.dir = dir;
    return result;
}
LocalGeo Transformation::operator* (LocalGeo& local) {
    LocalGeo result;
    result.pos = *(this) * local.pos;
    this->swap();
    this->m.transpose();
    Vector normal;
    for(int i = 0; i < 3; i++) {
        normal[i] = 0;
        for(int j = 0; j < 3; j++) {
            normal[i] += this->m.mat[i][j] * local.normal[j];
        }
    }
    normal.normalize();
    result.normal = normal;
    this->m.transpose();
    this->swap();
    return result;
}

// BRDF CLASS
BRDF::BRDF() {
    this->shininess = 0;
}
BRDF::BRDF(Vector kd, Vector ks, Vector ka, float shininess) {
    this->kd = kd;
    this->ks = ks;
    this->ka = ka;
    this->shininess = shininess;
}

// SAMPLE CLASS
Sample::Sample() {
    this->x = this->y = 0;
}
Sample::Sample(float x, float y) {
    this->x = x;
    this->y = y;
}
