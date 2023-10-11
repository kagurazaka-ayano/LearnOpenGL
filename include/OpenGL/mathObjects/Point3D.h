/**
 * @parent include/OpenGL/mathObjects
 * @file Point3D.h
 * @author ayano
 * @date 9/15/23
 *
*/

#ifndef OPENGL_POINT3D_H
#define OPENGL_POINT3D_H

#include <string>
#include <cmath>
#include <sstream>
#include "mathObjects/PointND.h"

class Point3D : public PointND<3> {
public:
    static Point3D ZERO;

    float x, y, z;

    explicit Point3D(const std::array<float, 3>& set);

    Point3D(const float& x, const float& y, const float& z);

    Point3D(const std::initializer_list<float>& set);

    Point3D();

};


#endif //OPENGL_POINT3D_H
