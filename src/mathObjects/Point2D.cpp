/*
 * @parent: src/mathObjects
 * @file: Point2D.cpp
 * @author: ayano
 * @date: 9/18/23
 * 
*/

#include "mathObjects/Point2D.h"

Point2D::Point2D(const float &x, const float &y) : x(x), y(y), PointND<2>({x, y}) {

}

Point2D::Point2D(const std::array<float, 2> &set) : PointND(set), x(set[0]), y(set[1]) {

}

Point2D::Point2D(const std::initializer_list<float> &std) : PointND(std), x(coord[0]), y(coord[1]) {

}

