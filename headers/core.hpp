/* Core classes needed for all operations (implementation on vector, matrices, etc) */

class Vector {
    public:

    float x, y, z;

    Vector(float, float, float);

    // op overloads
    Vector operator+ (const Vector&);
    Vector operator- (const Vector&);
    Vector operator* (const float&);
    Vector operator/ (const float&);

    Vector  normalize(void);
    float getLength();
};
