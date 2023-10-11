/*
 * @parent: src/glObjects
 * @file: Texture.cpp
 * @author: ayano
 * @date: 9/30/23
 * 
*/

#include "glObjects/Texture.h"


Texture::Texture(const std::string& name, unsigned int id): IPoolable(id, name) {

}

Texture::~Texture() = default;



