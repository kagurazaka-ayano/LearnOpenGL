/*
 * @parent: src/mathObjects
 * @file: Point3D.cpp
 * @author: ayano
 * @date: 9/18/23
 *
*/

#include "mathObjects/Point3D.h"

Point3D Point3D::ZERO = Point3D({0, 0, 0});

Point3D::Point3D(const std::array<float, 3> &set): PointND(set), x(set[0]), y(set[1]), z(set[2]){

}

Point3D::Point3D(const float &x, const float &y, const float &z) : PointND({x, y, z}), x(x), y(y), z(z){
}

Point3D::Point3D(const std::initializer_list<float> &set) : PointND(set), x(coord[0]), y(coord[1]), z(coord[2]) {

}

Point3D::Point3D() : PointND<3>(), x(0), y(0), z(0) {

}
