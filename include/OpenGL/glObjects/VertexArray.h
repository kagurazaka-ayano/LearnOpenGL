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
#include "utilities/utilities.h"

template<std::size_t N>
struct VertexArray{
    std::array<Vertex, N> vertices;
    float data[N * 7]{};
    VertexArray(const std::initializer_list<Vertex>& vertex){
        runtimeAssert(vertex.size() == N, fmt::format("Dimension provided in template argument ({0}) doesn't match the given array dimension ({1})", N, vertex.size()));
        std::copy(vertex.begin(), vertex.end(), vertices.begin());
        for (int i = 0; i < 7 * vertex.size(); i++){
            data[i] = (vertex.begin() + (i / 7))->data[i % 7];
        }
    }
};

#endif //OPENGL_VERTEXARRAY_H
