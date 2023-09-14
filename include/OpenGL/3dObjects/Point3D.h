#ifndef OPENGL_POINT3D_H
#define OPENGL_POINT3D_H

#include <string>
#include <cmath>
#include <sstream>

class Point3D {
public:
    float x, y, z;

    Point3D(const float& x, const float& y, const float& z);

    explicit Point3D(const float*& set);

    virtual ~Point3D() = default;

    float dist(const Point3D& p) const;

    Point3D normalize(int dim_x, int dim_y, int dim_z) const;

    Point3D operator +(const Point3D& p) const;

    Point3D operator +(const float*& shift) const;

    Point3D operator -(const Point3D& p) const;

    Point3D operator -(const float*& shift) const;

    explicit operator std::string() const;

};


#endif //OPENGL_POINT3D_H
