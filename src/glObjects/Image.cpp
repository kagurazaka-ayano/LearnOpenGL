/*
 * @parent: src/glObjects
 * @file: Image.cpp
 * @author: ayano
 * @date: 9/30/23
 * 
*/

#include "glObjects/Image.h"

Image::~Image() {
    FileManager::freeImage(data);
}

Image::Image(const std::string &path, const Point2D& dimension, int channel) :
path(path),
dimension(dimension),
data(FileManager::getImage(
        path,
        static_cast<int>(dimension.x),
        static_cast<int>(dimension.y),
        channel
        )){
}

Image::Image(const std::string &path, int width, int height, int channel) :
path(path),
dimension(Point2D(static_cast<float>(width),static_cast<float>(height))),
data(FileManager::getImage(path, width, height, channel)){

}
