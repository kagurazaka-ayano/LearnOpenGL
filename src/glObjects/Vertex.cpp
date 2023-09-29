/*
 * @parent: src/glObjects
 * @file: Vertex.cpp
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#include "glObjects/Vertex.h"

Vertex::Vertex(const Point3D &position, const Color &color) : position(position), color(color) {
    std::copy(position.coord.begin(), position.coord.end(), data.begin());
    std::copy(color.coord.begin(), color.coord.end(), data.begin() + position.coord.size());
}

Vertex::Vertex(const std::initializer_list<float> &set) : position(sliceArray<float, 3>(set, 0)), color(sliceArray<float, 4>(set, 3),
                                                                                                        ColorSpaceRGB::Instance()){
    std::copy(set.begin(), set.end(), data.begin());
}

Vertex::Vertex(): position(Point3D::ZERO), color(Color::WHITE), data({0, 0, 0, 0, 0, 0, 0}) {

}

Vertex &Vertex::operator=(Vertex &&other) noexcept {
    if (this != &other)
    {
        position = std::move(other.position);
        color = std::move(other.color);
    }
    return *this;
}

Vertex::Vertex(const Vertex &other) {
    this->color = other.color;
    this->position = other.position;
    this->data = other.data;
}

Vertex &Vertex::operator=(const Vertex &other) {
    if(this != &other){
        this->color = other.color;
        this->position = other.position;
        this->data = other.data;
    }
    return *this;
}
