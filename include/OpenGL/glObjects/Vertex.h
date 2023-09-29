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
#include "utilities/utilities.h"
#include <mathObjects/Color.h>

struct Vertex{
    Point3D position;
    Color color;
    std::array<float, 7> data{};
    Vertex& operator=(Vertex&& other) noexcept;
    Vertex& operator=(const Vertex& other);
    Vertex();
    Vertex(const Point3D& position, const Color& color);
    Vertex(const std::initializer_list<float>& set);
    Vertex(const Vertex& other);
};

#endif //OPENGL_VERTEX_H
