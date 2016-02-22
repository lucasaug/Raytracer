/* Core classes needed for all operations (implementation on vector, matrices, etc) */

#ifndef LAFO_RAYTRACER_CORE

#define LAFO_RAYTRACER_CORE

class Vector {
    public:

    float x, y, z;

    Vector();
    Vector(float, float, float);

    bool   operator== (const Vector&);
    bool   operator!= (const Vector&);
    void   operator=  (const Vector&);
    Vector operator+  (const Vector&);
    Vector operator-  (const Vector&);
    Vector operator*  (const float&);
    Vector operator/  (const float&);
    float& operator[] (int);

    void   normalize(void);
    float  dot(Vector);
    Vector cross(Vector);
    float  getLength();
};

class Ray {
    public:

    Vector point;
    Vector dir;

    Ray();
    Ray(const Vector&, const Vector&);
};

class LocalGeo {
    public:
    Vector pos;
    Vector normal;

    LocalGeo();
    LocalGeo(Vector, Vector);
};

class Matrix {
    public:
    float mat[4][4];

    Matrix();
    Matrix(float[16]);

    void identity();
    void transpose();
    // creates the appropriate matrices for transformations
    void scale(Vector);
    void rotate(Vector, float);
    void translate(Vector);

    bool   operator== (const Matrix&);
    bool   operator!= (const Matrix&);
    Matrix operator+  (const Matrix&);
    Matrix operator-  (const Matrix&);
    void   operator=  (const Matrix&);
    Matrix operator*  (const Matrix&);
    Matrix operator*  (float);
    Matrix operator/  (float);
};

class Transformation {
    public:
    Matrix m, minv;

    Transformation();

    // resets the transformation to do nothing
    void reset();
    // swaps m and minv
    void swap();
    // each of these transforms multiply the currently stored transform
    void scale(Vector);
    void rotate(Vector, float);
    void translate(Vector);

    Vector   operator* (Vector&);
    Ray      operator* (Ray&);
    LocalGeo operator* (LocalGeo&);
};

class BRDF {
    public:
    Vector kd, ks, ka;
    float shininess;

    BRDF();
    BRDF(Vector, Vector, Vector, float);
};

class Sample {
    public:
    float x, y;

    Sample();
    Sample(float, float);
};

#endif
