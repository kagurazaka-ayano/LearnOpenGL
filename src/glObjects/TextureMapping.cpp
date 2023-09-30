/*
 * @parent: src/glObjects
 * @file: TextureMapping.cpp
 * @author: ayano
 * @date: 9/29/23
 * 
*/

#include "glObjects/TextureMapping.h"

TextureMapping::TextureMapping(const std::array<Point2D, 3> &mapping) : mapping(mapping) {
    int idx = 0;
    for(const auto& i : mapping){
        data[idx++] = i.x;
        data[idx++] = i.y;
    }
}
