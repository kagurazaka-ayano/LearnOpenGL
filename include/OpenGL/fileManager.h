#ifndef OPENGL_FILEMANAGER_H
#define OPENGL_FILEMANAGER_H

#include <fstream>
#include <string>
#include <spdlog/spdlog.h>

enum class SHADER_TYPE{
    FRAG,
    VERT
};

const std::string SHADER_ROOT{"../src/shaders/"};
const std::string SHADER_TYPE_REF[]{"frag", "vert"};

std::string getShader(const SHADER_TYPE& type, const std::string& name = "default");

bool writeShader(const SHADER_TYPE& type, const std::string& name, const std::string& content);

#endif //OPENGL_FILEMANAGER_H


