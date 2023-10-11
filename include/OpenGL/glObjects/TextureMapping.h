/**
 * @parent include/OpenGL/glObjects
 * @file TextureMapping.h
 * @author ayano
 * @date 9/29/23
 * @brief
*/

#ifndef OPENGL_TEXTUREMAPPING_H
#define OPENGL_TEXTUREMAPPING_H

#include "mathObjects/Point2D.h"

struct TextureMapping{
    std::array<Point2D, 3> mapping;
    float data[6]{0};
    explicit TextureMapping(const std::array<Point2D, 3>& mapping);
};

#endif //OPENGL_TEXTUREMAPPING_H
