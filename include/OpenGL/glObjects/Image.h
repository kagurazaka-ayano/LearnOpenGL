/**
 * @parent: include/OpenGL/glObjects
 * @file: Image.h
 * @author: ayano
 * @date: 9/30/23
 * 
*/

#ifndef OPENGL_IMAGE_H
#define OPENGL_IMAGE_H
#include <string>
#include "mathObjects/Point2D.h"
#include "managers/FileManager.h"

/**
 * @brief a image
 */
struct Image {
public:
    Point2D dimension;
    std::string path;
    unsigned char* data;
    Image(const std::string& path, int width, int height, int channel);
    Image(const std::string& path, const Point2D& dimension, int channel);
    virtual ~Image();
};


#endif //OPENGL_IMAGE_H
