/*
 * @parent: src/glObjects
 * @file: VertexArray.h
 * @author: ayano
 * @date: 9/20/23
 * 
*/

#ifndef OPENGL_VERTEXARRAY_H
#define OPENGL_VERTEXARRAY_H

#include <vector>
#include <glObjects/Vertex.h>
#include <cassert>

template<std::size_t N>
struct VertexArray{
    std::vector<Vertex> vertices;
    float data[N * 6]{};
    VertexArray(const std::initializer_list<Vertex>& vertex) : vertices(vertex) {
        assert(vertex.size() == N);
        for (int i = 0; i < 6 * vertex.size(); i++){
            data[i] = (vertex.begin() + (i / 6))->data[i % 6];
        }
    }
};

#endif //OPENGL_VERTEXARRAY_H
