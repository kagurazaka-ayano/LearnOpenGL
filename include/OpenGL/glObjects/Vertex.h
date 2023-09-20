/*
 * @parent: src/glObjects
 * @file: Vertex.h
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#ifndef OPENGL_VERTEX_H
#define OPENGL_VERTEX_H
#include <mathObjects/Point3D.h>
#include <utilities/utilities.h>

struct Vertex{
    Point3D position;
    Point3D color;
    std::array<float, 6> data{};
    Vertex(const Point3D& position, const Point3D& color);
    Vertex(const std::initializer_list<float>& set);
};

#endif //OPENGL_VERTEX_H
