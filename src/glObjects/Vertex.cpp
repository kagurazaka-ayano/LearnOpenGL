/*
 * @parent: src/glObjects
 * @file: Vertex.cpp
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#include "glObjects/Vertex.h"

Vertex::Vertex(const Point3D &position, const Point3D &color) : position(position), color(color) {
    std::copy(position.coord.begin(), position.coord.end(), data.begin());
    std::copy(color.coord.begin(), color.coord.end(), data.begin() + position.coord.size());
}

Vertex::Vertex(const std::initializer_list<float> &set) : position(sliceArray<float, 3>(set, 0)), color(sliceArray<float, 3>(set, 3)){
    std::copy(set.begin(), set.end(), data.begin());
}
