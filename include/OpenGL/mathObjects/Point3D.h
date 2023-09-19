#ifndef OPENGL_POINT3D_H
#define OPENGL_POINT3D_H

#include <string>
#include <cmath>
#include <sstream>
#include <mathObjects/PointND.h>

class Point3D : PointND<3> {
public:
    float x, y, z;

    explicit Point3D(const std::array<float, 3>& set);

    Point3D(const float& x, const float& y, const float& z);

    Point3D(const std::initializer_list<float>& set);

};


#endif //OPENGL_POINT3D_H
