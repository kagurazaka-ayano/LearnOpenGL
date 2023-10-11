/**
 * @parent include/OpenGL/managers
 * @file TextureManager.h
 * @author ayano
 * @date 9/30/23
 * 
*/

#ifndef OPENGL_TEXTUREMANAGER_H
#define OPENGL_TEXTUREMANAGER_H
#include <string>
#include <unordered_map>
#include "glObjects/Texture.h"
#include "utilities/SingletonAbstract.hpp"
#include "utilities/PoolAbstract.h"

class TextureManager : public SingletonAbstract<TextureManager>, public PoolAbstract<Texture>{
    friend class SingletonAbstract<TextureManager>;
public:
    TextureManager(const TextureManager& other) = delete;
    TextureManager& operator=(const TextureManager& other) = delete;
    Texture getTexture(const std::string& name, int width, int height, int channelCount);
    Texture getTexture(const std::string& name, const Image& image);
private:
    TextureManager() = default;
};


#endif //OPENGL_TEXTUREMANAGER_H
