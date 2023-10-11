/**
 * @parent include/OpenGL/glObjects
 * @file Texture.h
 * @author ayano
 * @date 9/30/23
 * 
*/

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include <string>

#include "mathObjects/Point2D.h"
#include "glObjects/Image.h"
#include "utilities/PoolAbstract.h"


struct Texture : public IPoolable {
public:
    Texture(const std::string& name, unsigned int id);
    virtual ~Texture();
};


#endif //OPENGL_TEXTURE_H
