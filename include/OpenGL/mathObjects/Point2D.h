/*
 * @parent: src/mathObjects
 * @file: Point2D.h
 * @author: ayano
 * @date: 9/18/23
 * 
*/

#ifndef OPENGL_POINT2D_H
#define OPENGL_POINT2D_H

#include <mathObjects/PointND.h>

class Point2D : PointND<2> {
public:
    float x, y;

    explicit Point2D(const std::array<float, 2>& set);

    Point2D(const float& x, const float& y);

    Point2D(const std::initializer_list<float>& set);
};


#endif //OPENGL_POINT2D_H
